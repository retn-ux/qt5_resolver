#include "pch.h"
#include "Resolver.h"
#include <sredefs.h>
#include <Asm.h>
#include <Auxiliary.h>
#include <ByteArray.h>
#include <algorithm>
#include <sstream>
using namespace Script::Memory;










Gauge metaObject(HANDLE hProcess,Gauge fmetaObject, Gauge obj) {
    Gauge ret=0;
    if (DbgIsRunning() != true) {
        ret = boom(fmetaObject, obj);
    }
    else {
        Print("STOP");
    }
    
    return ret;
}


//获取所有的寄存器数据，后面返回当前地址时全部恢复
void GetAllReg(CommomReg* regs) {
    using namespace Script::Register;
    regs->eax = GetEAX();
    regs->ebx = GetEBX();
    regs->ecx = GetECX();
    regs->edx = GetEDX();
    regs->edi = GetEDI();
    regs->esi = GetESI();
    regs->eip = GetEIP();
    regs->eflag = GetCFLAGS();
}

void SetAllReg(CommomReg regs) {
    using namespace Script::Register;
    SetEAX(regs.eax);
    SetEBX(regs.ebx);
    SetECX(regs.ecx);
    SetEDX(regs.edx);
    SetEDI(regs.edi);
    SetESI(regs.esi);
    SetEIP(regs.eip);
    SetCFLAGS(regs.eflag);
}



dword boom(dword fmetaObject, dword this_ptr) {
    using namespace Script::Debug;
    using namespace Script::Register;
    using namespace Script::Stack;
    using namespace std;
    CommomReg regs;
    GetAllReg(&regs);
    //准备栈和寄存器
    GUARD_GENTLE(Push(regs.eip), 0);
    GUARD_GENTLE(SetECX(this_ptr), 0);
    GUARD_GENTLE(SetEIP(fmetaObject), 0);
    duint eip_value = 0;
    //执行metaObject函数，staticMetaObject分为动态和静态

    do {
        StepOver();
        eip_value = GetEIP();

    } while (eip_value != regs.eip);
    dword eax_value = GetEAX();
    //恢复寄存器
    SetAllReg(regs);
    return eax_value;
}








bool GetObjectCenterInfo(HANDLE hd,duint staticMetaObject,CoarseData *out) {
    using namespace Script::Memory;
    //获取静态元数据对象
    CMetaObject aobj;
    GUARD_GENTLE(ReadMetaObjectData(hd,staticMetaObject, &aobj), false);
    out->addr = aobj;
    GUARD_GENTLE(out->addr.data_addr != 0, false);
    GUARD_GENTLE(out->addr.stringdata_addr != 0, false);
    //获取QMetaObject.data的content
    GUARD_GENTLE(ReadMDContent(hd,aobj.data_addr, &out->data.content),false)
    if (out->data.content.revision == 0) {
        return false;
    }
    //获取QMetaObject.data的信号函数签名
    duint mdSignalStart = aobj.data_addr + sizeof(duint) * out->data.content.method_desc_offset;
    ReadDesc(hd, mdSignalStart, out->data.content.signalCount, &out->data.signal);
    //获取QMetaObject.data的槽函数签名
    duint mdSlotStart = mdSignalStart + out->data.content.signalCount * sizeof(MDMethodDesc);
    ReadDesc(hd,mdSlotStart, out->data.content.method_count - out->data.content.signalCount,&out->data.slot);

    //获取QMetaObject.stringdata的data
    vector<string> sign_str;
    ReadMethodInfo(hd,aobj.stringdata_addr, &sign_str);
    GUARD_GENTLE(sign_str.size() > 0, false);
    //获取类名称
    out->strdata.className=sign_str[0];
    sign_str.erase(sign_str.begin());
    //这里是因为信号被另一个信号连接时信号会被置于"\x0"之下
    //也就是说按照正常通过signalCount计算索引时，无法从slot中查找到这些被当作slot的signal
    //而且这种信号之间的连接并不在ConnectionList中，而是通过硬编码的索引利用activate路由到qt_static_metacall,
    AbjustSlotIndex(sign_str, out->data.signal, out->data.slot);
    out->strdata.signal = GetSpecSign(sign_str, out->data.signal);
    out->strdata.slot = GetSpecSign(sign_str, out->data.slot);
    return true;
}


bool ReadMetaObjectData(HANDLE hd,duint addr, CMetaObject *out) {
    using namespace Script::Memory;
    GUARD_GENTLE(ReadMemory(tovptr(addr), out, sizeof(CMetaObject), hd), false);
    return true;
}


int SignaleOffset(vector<CoarseData>& obj) {
    int offset = 0;
    for (size_t i = 1; i < obj.size(); i++) {
        offset += obj[i].data.content.signalCount;
    }
    return offset;
}



duint GetPrivByObj(HANDLE hd,dword obj_addr) {
    obj_addr += 4;
    duint obj_private=0;
    ReadMemory(tovptr(obj_addr), &obj_private, sizeof(obj_private), hd);
    return obj_private;
}


duint GetConnectList(HANDLE hd,dword obj_priv_addr) {
    duint ret=0;
    ReadMemory(tovptr(obj_priv_addr+0x24), &ret, sizeof(ret), hd);
    return ret;
}


vector<ConnectionList> ReadConnectListData(HANDLE hd,duint connectList_addr) {
    vector<ConnectionList> ret;
    ConnectionList m;
    ZeroMemory(&m, sizeof(m));
    //读取QTypedArrayData的地址，由于类的内存布局基类在前面，并且没有虚函数，QTypedArrayData的地址=QArrayData的地址
    dword final_addr;
    GUARD_GENTLE(ReadMemory(tovptr(connectList_addr), &final_addr,sizeof(final_addr),hd),ret)
    GUARD_GENTLE(final_addr != 0, ret);
    QArrayDataHdr header;
    GUARD_GENTLE(ReadMemory(tovptr(final_addr), &header, sizeof(header), hd), ret);
    GUARD_GENTLE(header.size != 0, ret);
    dword data_addr = final_addr + header.offset;
    for (int i = 0; i < header.size; i++) {
        GUARD_GENTLE(ReadMemory(tovptr(data_addr), &m, sizeof(m), hd), ret);
        ret.push_back(m);
        data_addr += sizeof(m);
    }
    return ret;
}


dword GetSignalIndex(vector<CoarseData>& obj_list, string name) {
    using std::find;
    using std::distance;
    bool IsFindLoaclIndexes=false;
    dword offset = 0;
    
    for (auto& item : obj_list) {
        if (IsFindLoaclIndexes == false) {
            //查找本地索引
            vector<MethodSign>& signal = item.strdata.signal;
            for (size_t t = 0; t < signal.size(); t++) {
                if (signal[t].name == name) {
                    offset = t;
                    IsFindLoaclIndexes = true;
                    break;
                }
            }
        }
        else {
            //继续计算相对索引
            offset += item.data.content.signalCount;
        }
        
    }
    return offset;
}



duint GetMetaObject(HANDLE handle , Gauge obj_addr) {
    //任何继承了QObject的对象，虚表的第一项为metaObject
    Gauge vtable_addr;
    GUARD_GENTLE(ReadMemory(tovptr(obj_addr), &vtable_addr, sizeof(vtable_addr), handle), 0);
    Gauge fmetaObject_addr;
    GUARD_GENTLE(ReadMemory(tovptr(vtable_addr), &fmetaObject_addr, sizeof(fmetaObject_addr), handle), 0);
    //直接执行metaObject函数
    return metaObject(handle,fmetaObject_addr, obj_addr);
}




MethodSign FindSlotName(vector<CoarseData>& in, int method_offset,int method_relative) {
    int offset = 0;
    MethodSign ret;
    for (size_t i = in.size(); i != 0; i--) {
        offset += in[i - 1].data.content.method_count;
        if (offset > method_offset && method_relative-1 < in[i - 1].strdata.slot.size()) {
            ret = in[i - 1].strdata.slot[method_relative-1];
            break;
        }
    }
    return ret;
}




void PrintInfo(ElaborateData &in) {
    if (in.sender.sender_name.size() != 0) {
        Print("class name :%s\n", in.sender.sender_name.c_str());
    }
    Print("address info:\n");
    if (in.sender.staticMetaObject != 0) {
        Print(" staticMetaObject address:0x%X\n", in.sender.staticMetaObject);
    }
    if (in.sender.QObjectPrivateAddr != 0) {
        Print(" QObjectPrivate address:0x%X\n", in.sender.QObjectPrivateAddr);
    }
    if (in.sender.ConnectionListAddr != 0) {
        Print(" ConnectionList address:0x%X\n", in.sender.ConnectionListAddr);
    }
    Print("Signal:\n");
    for (auto& i : in.connect_info) {       
        Print(" name:%s param:", i.signal.name.c_str());
        for (auto& param : i.signal.param) {
            Print("%s ", param.c_str());
        }
        Print("\n");
        for (auto& slot : i.slot) {
            Print("     -> class name:%s, MD object address:0x%X, qt_meta_call:0x%X, method index:0x%X, method name:%s, param:", slot.class_name.c_str(),slot.obj, 
                slot.qt_static_metacall, slot.slot_index,slot.slot.name.c_str());
            for (auto& param : slot.slot.param) {
                Print("%s ", param.c_str());
            }
            Print("\n");
        }   
    }
    Print("Slot:\n");
    for (auto& i : in.slot) {
        Print(" name:%s param:", i.name.c_str());
        for (auto& param : i.param) {
            Print("%s ", param.c_str());
        }
        Print("\n");
    }
    Print("\n");

}


bool GetObjInfo(HANDLE hd,duint md_addr, vector<CoarseData> *out) {
   
    duint taddr = md_addr;
    do {
        CoarseData core;
        GUARD_GENTLE(GetObjectCenterInfo(hd,taddr, &core),false)
        if (taddr != 0) {
            out->push_back(core);
        }
        taddr = core.addr.super;
    } while (taddr != 0);
    return true;
}

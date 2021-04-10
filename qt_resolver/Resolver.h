#pragma once

#include <map>
#include <string>
#include <vector>
#include <SREMemory.h>
#include "MetaData.h"
#include "pluginmain.h"
#include "MetaStrData.h"

using std::map;
using std::pair;
using std::string;
using std::vector;

#define Print _plugin_logprintf
#define STRINGDATA_OFFSET 0x4
#define DATA_OFFSET 0x8
#define GUARD_GENTLE(a,b)\
	if(!(a))return b;

typedef DWORD dword;
typedef unsigned int uint;
typedef USHORT ushort;
 
struct CMetaObject {
	dword super;
	dword stringdata_addr;
	dword data_addr;
	dword qt_static_metacall;
};

struct CoarseData {
	CMetaObject addr;
	CMetaData data;
	CMetaStrData strdata;
};

struct GridData {
	string class_name;
	duint obj;
	duint qt_static_metacall;
	int slot_index;
	MethodSign slot;
};

struct ConnectData {
	MethodSign signal;
	vector<GridData> slot;
	void clear() {
		signal.name.clear();
		signal.param.clear();
		slot.clear();
	}
};
struct SENDER_INFO {
	duint staticMetaObject;
	CMetaObject signpost;
	duint QObjectPrivateAddr;
	duint ConnectionListAddr;
	string sender_name;
	void clear() {
		ZeroMemory(&staticMetaObject, sizeof(staticMetaObject));
		ZeroMemory(&signpost, sizeof(signpost));
		ZeroMemory(&QObjectPrivateAddr, sizeof(QObjectPrivateAddr));
		ZeroMemory(&ConnectionListAddr, sizeof(ConnectionListAddr));
		sender_name.clear();
	}
};

struct RECEIVER_INFO {
	
	duint staticMetaObject;
};




struct ElaborateData {
	SENDER_INFO sender;
	vector<ConnectData> connect_info;
	vector<MethodSign> slot;
	void clear() {
		sender.clear();
		connect_info.clear();
		slot.clear();
	}
};







struct Connection {
	dword sender_ptr;
	dword receiver_ptr;
	union {
	dword callFunction_ptr;
	dword slotObj_ptr;
	};
	Connection* nextConnectionList;
	dword next;
	dword prev;
	dword argumentTypes;	//QAtomicPointer<const int>
	dword ref;				//QAtomicInt
	ushort method_offset;
	ushort method_relative;
	dword signal_index : 27;// In signal range (see QObjectPrivate::signalIndex())
	ushort connectionType : 3;// 0 == auto, 1 == direct, 2 == queued, 4 == blocking
	ushort isSlotObject : 1;
	ushort ownArgumentTypes : 1;
};


struct ConnectionList {
	dword first;
	dword next;
};



//QArrayData的头结构
struct QArrayDataHdr {
	uint ref;//引用计数
	int size;                //元素的个数
	uint alloc : 31;         //分配的内存块的个数
	uint capacityReserved : 1;//适应模式
	uint offset;			//// in bytes from beginning of header  定位指针
};

struct CommomReg {
	duint eax;
	duint ebx;
	duint ecx;
	duint edx;
	duint edi;
	duint esi;
	duint esp;
	duint ebp;
	duint eip;
	duint eflag;
};







//获取地址函数
bool ReadMetaObjectData(HANDLE dh,duint addr,CMetaObject *out);
Gauge metaObject(HANDLE hProcess,Gauge fmetaObject,Gauge obj);
duint GetPrivByObj(HANDLE hd, dword obj_addr);
duint GetConnectList(HANDLE hd,dword obj_priv_addr);
dword boom(dword fmetaObject, dword this_ptr);
duint GetMetaObject(HANDLE handle,dword obj_addr);
//------------
bool GetObjectCenterInfo(HANDLE hd,duint staticMetaObject,CoarseData *out);

vector<ConnectionList> ReadConnectListData(HANDLE hd, duint connectList_addr);

dword GetSignalIndex(vector<CoarseData>& obj_list,string name);
MethodSign FindSlotName(vector<CoarseData>& in, int method_offset, int method_relative);

bool GetObjInfo(HANDLE hd,duint md_addr, vector<CoarseData> *out);

void PrintInfo(ElaborateData &in);


#include "pch.h"
#include "DpMain.h"
#include <sredefs.h>

vector<ElaborateData> DpObjMain(SRE_HANDLE hd,duint obj) {
	vector<ElaborateData> ret;
	ElaborateData subItem;
	subItem.sender.staticMetaObject = GetMetaObject(hd, obj);
	GUARD_GENTLE(subItem.sender.staticMetaObject != 0, ret);
	vector<CoarseData> coarse_data;
	GUARD_GENTLE(GetObjInfo(hd, subItem.sender.staticMetaObject, &coarse_data), ret);
	vector<CoarseData> bs_coarse_data = coarse_data;
	for (auto& item : bs_coarse_data) {
		subItem.sender.signpost.data_addr = item.addr.data_addr;
		subItem.sender.signpost.stringdata_addr = item.addr.stringdata_addr;
		subItem.sender.signpost.qt_static_metacall = item.addr.qt_static_metacall;
		subItem.sender.signpost.super = item.addr.qt_static_metacall;
		subItem.sender.sender_name = item.strdata.className;
		subItem.slot = item.strdata.slot;
		duint obj_priv = GetPrivByObj(hd, obj);
		subItem.sender.QObjectPrivateAddr = obj_priv;
		if (obj_priv == 0) {
			continue;
		}
		duint connect_list = GetConnectList(hd, obj_priv);
		subItem.sender.ConnectionListAddr = connect_list;
		for (auto& signal_item : item.strdata.signal) {
			ConnectData cdata;
			GridData gdata;
			cdata.signal = signal_item;
			if (connect_list != 0) {
				dword index = GetSignalIndex(coarse_data, signal_item.name);
				vector<ConnectionList> data = ReadConnectListData(hd, connect_list);
				if (data.size() == 0) continue;
				Connection list;
				duint iter=0;
				//可能槽函数并没有连接
				if (index <= data.size()) {
					iter = data[index].first;
					do {
						if (!ReadMemory(tovptr(iter), &list, sizeof(list), hd)) {
							break;
						}
						vector<CoarseData> mid_data;
					
						duint staicMetaObject = GetMetaObject(hd, list.receiver_ptr);
						if (!GetObjInfo(hd, staicMetaObject, &mid_data)) {
							continue;
						}
						MethodSign mid_sign = FindSlotName(mid_data, list.method_offset, list.method_relative);

						gdata.class_name = mid_data[0].strdata.className;
						gdata.obj = staicMetaObject;
						gdata.qt_static_metacall = mid_data[0].addr.qt_static_metacall;
						gdata.slot = mid_sign;
						gdata.slot_index = list.method_relative;
						cdata.slot.push_back(gdata);
						iter = list.next;
					} while (iter != 0);		
				}
			}
			subItem.connect_info.push_back(cdata);
		}
		ret.push_back(subItem);
		subItem.clear();
		coarse_data.erase(coarse_data.begin());
		subItem.sender.staticMetaObject = item.addr.super;
	}

	return ret;
}
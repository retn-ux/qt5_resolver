#pragma once
#include "pluginmain.h"
#include "MetaData.h"
#include <vector>
#include <SREMemory.h>
#include <map>
#include <string>
using std::string;
using std::vector;
using std::map;

struct MSDContent {
	duint sep;		//分隔符0xFFFFFFF
	duint len;		//字符串的长度
	duint fill;		//填充为0
	duint offset;	//这里的偏移是相对当前项的偏移
};

struct MethodSign {
	string name;
	vector<string> param;
};



struct CMetaStrData {
	string className;
	vector<MethodSign> signal;
	vector<MethodSign> slot;
};

vector<MethodSign> GetSpecSign(vector<string>& meta, vector<MDMethodDesc>& desc);
void AbjustSlotIndex(vector<string>& meta, vector<MDMethodDesc>& signal, vector<MDMethodDesc>& slot);
void ReadMethodInfo(HANDLE hd,duint addr, vector<string>* out);
vector<MSDContent> ReadMSDContent(duint addr);
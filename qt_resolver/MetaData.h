#pragma once
#include "pluginmain.h"
#include <vector>

using std::vector;

struct MDContent {
	duint revision;
	duint classname;
	duint class_count;
	duint class_desc_offset;
	duint method_count;
	duint method_desc_offset;
	duint properties_count;
	duint properties_desc_offset;
	duint enums_sets_count;
	duint enums_sets_desc_offset;
	duint constructors_count;
	duint constructors_desc_offset;
	duint flag;
	duint signalCount;
};



struct MDMethodDesc {
	duint name;		//Method名称在stringData中的索引
	duint argc;
	duint parameters;	//参数在IdxData中的偏移	
	duint tag;
	duint flags;
};


struct CMetaData {
	MDContent content;
	vector<MDMethodDesc> signal;
	vector<MDMethodDesc> slot;
};
bool ReadMDContent(HANDLE hd, duint start, MDContent* out);
void ReadDesc(HANDLE hd, duint start, duint num, vector<MDMethodDesc>* out);
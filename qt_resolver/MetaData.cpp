#include "pch.h"
#include "MetaData.h"
#include <sredefs.h>
#include <SREMemory.h>
#include <algorithm>
using namespace Script::Memory;
using std::copy;



bool ReadMDContent(HANDLE hd,duint start, MDContent *out) {
    GUARD_GENTLE(ReadMemory(tovptr(start), out, sizeof(MDContent), hd),false)
    return true;
}



void ReadDesc(HANDLE hd,duint start,duint num, vector<MDMethodDesc> *out) {

    for (duint i = 0; i < num; i++) {
        MDMethodDesc item;
        ReadMemory(tovptr(start), &item, sizeof(MDMethodDesc), hd);
        out->push_back(item);
        start += sizeof(MDMethodDesc);
    }
}

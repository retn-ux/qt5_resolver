#include "pch.h"
#include "MetaStrData.h"
using namespace Script::Memory;

vector<MSDContent> ReadMSDContent(duint addr) {
    vector<MSDContent> ret;
    MSDContent m;
    do {
        duint szRead;
        Read(addr, &m, sizeof(MSDContent), &szRead);
        if (m.sep == 0xFFFFFFFF&&m.fill==0) {
            ret.push_back(m);
        }
        addr += sizeof(MSDContent);
    } while (m.sep == 0xFFFFFFFF && m.fill == 0);
    return ret;

}



void ReadMethodInfo(HANDLE hd,duint addr, vector<string> *out) {
    vector<MSDContent> dsc = ReadMSDContent(addr);

    char np[1000];
    for (const auto& i : dsc) {
        duint itemIndex = i.offset + addr;

        ReadMemory(tovptr(itemIndex), np, i.len + 1, hd);
        out->push_back(np);
        ZeroMemory(np, sizeof(np));
        addr += sizeof(MSDContent);
    }
}

void AbjustSlotIndex(vector<string>& meta, vector<MDMethodDesc>& signal, vector<MDMethodDesc>& slot) {

    size_t index = -1;
    for (size_t i = 0; i < meta.size(); i++) {
        if (meta[i].size() == 0) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        vector<MDMethodDesc> m;
        for (auto& i : signal) {
            if (i.name - 1 > index) {
                m.push_back(i);
            }
        }
        slot.insert(slot.begin(),m.begin(),m.end());
    }

}


vector<MethodSign> GetSpecSign(vector<string> &meta, vector<MDMethodDesc> &desc) {
    vector<MethodSign> ret;
    if (meta.size() <= 0) return ret;
    
    for (duint i = 0; i < desc.size(); i++) {
        MethodSign m;
        m.name = meta[desc[i].name - 1];
        if (desc[i].argc > 0) {
            for (duint d = 0; d < desc[i].argc; d++) {
                if (desc[i].name + d < meta.size()) {
                    m.param.push_back(meta[desc[i].name + d]);
                }
            }
        }
        ret.push_back(m);
    }
    return ret;
}




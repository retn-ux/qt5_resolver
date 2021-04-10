#include "pch.h"
#include <ImageDefs.h>
#include <CorTableMgr.h>
#include <CorAux.h>

/*
DWORD GetCountFormMask(ULONGLONG mask) {
	DWORD count = 0;
	for (ULONGLONG i : ImgMdtStmMaskArray) {
		if ((mask & i) == i) {
			count++;
		}
	}
	return count;
}


LPVOID GetMethodTable(LPVOID begin) {
	return LPVOID((DWORD)begin + 0x11A4);
}

IImgMdtTable* CreateTableInstance(DWORD index) {
	return InstanceArray[index]();
}

ImgMdtMethodTableEx::ImgMdtMethodTableEx(ImgMdtMethodTableEx&& m) {
	this->metaDataMethodTable = std::move(m.metaDataMethodTable);
	m.metaDataMethodTable.clear();
	this->begin = m.begin;
	this->mask = m.mask;
	this->mode = m.mode;
	m.begin = nullptr;
	m.mask = 0;
	m.mode = ImageMode::File;
}

ImgMdtMethodTableEx::ImgMdtMethodTableEx(ImgMdtMethodTableEx& m) {
	std::copy(m.metaDataMethodTable.begin(), m.metaDataMethodTable.end(), this->metaDataMethodTable.begin());
	this->begin = m.begin;
	this->mask = m.mask;
	this->mode = m.mode;
}

DWORD ImgMdtMethodTableEx::init(LPVOID base, DWORD size, ULONGLONG mask, ImageMode mode, HANDLE hProcess) {
	using dynamic::Image::MDTMethod;
	ASSERT_ADDR(base)
	this->mask = mask;
	this->mode = mode;
	this->begin = base;
	if (mode == ImageMode::Memory) {
		ASSERT_HANDLE(hProcess)
	}
	for (DWORD i = 0; i < size; i++) {
		if (mode == ImageMode::File) {
			metaDataMethodTable.push_back((MDTMethod*)base);	
		}
		else if (mode == ImageMode::Memory) {
			metaDataMethodTable.push_back(new MDTMethod);
			SIZE_T size;
			ReadProcessMemory(hProcess,base,metaDataMethodTable[i],sizeof(MDTMethod),size)
		}	
		base = LPVOID((DWORD)base + GetSize());
	}
	return 0;

}

MDTMethod ImgMdtMethodTableEx::GetMethodTable(DWORD index) {
	using dynamic::Image::MDTMethod;
	GUARD_GENTLE(begin == nullptr, MDTMethod())
	return *metaDataMethodTable[index - 1];
}

DWORD ImgMdtMethodTableEx::write(MDTMethod& md, DWORD index, HANDLE hProcess) {
	ASSERT_ADDR(begin)
	if (mode == ImageMode::File) {
		memcpy(this->metaDataMethodTable[index], &md, sizeof(MDTMethod));
	}
	else if (mode == ImageMode::Memory) {
		ASSERT_HANDLE(hProcess)
		SIZE_T size;
		LPVOID lpBase = LPVOID((DWORD)begin + GetSize() * index - 2);
		WriteProcessMemory(hProcess, lpBase,&md,sizeof(metaDataMethodTable),size)
		memcpy(this->metaDataMethodTable[index-1], &md, sizeof(MDTMethod));
	}
	return 0;
}

ImgMdtMethodTableEx::~ImgMdtMethodTableEx(){
	if (this->metaDataMethodTable.size() != 0 && this->mode == ImageMode::Memory) {
		for (auto i : metaDataMethodTable) {
			if (i != nullptr) {
				delete i;
				i = nullptr;
			}		
		}
	}
}


DWORD ImgMdtStmHdr::init(LPVOID lpBaseAddress, ImageMode mode, HANDLE hProcess) {
	ASSERT_ADDR(lpBaseAddress)
	this->mode = mode;
	this->begin = lpBaseAddress;
	if (mode == ImageMode::File) {
		metaDataStreamHeader = (MDStreamHeader*)lpBaseAddress;
	}
	else if (mode == ImageMode::Memory) {
		ASSERT_HANDLE(hProcess)
		metaDataStreamHeader = new MDStreamHeader;
		SIZE_T size;
		ReadProcessMemory(hProcess,lpBaseAddress,metaDataStreamHeader,sizeof(MDStreamHeader),size)
	}
	return 0;
}


ImgMdtStmHdr::ImgMdtStmHdr(ImgMdtStmHdr& m) {
	this->metaDataStreamHeader = m.metaDataStreamHeader;
	this->begin = m.begin;
	this->mode = m.mode;
}
ImgMdtStmHdr::ImgMdtStmHdr(ImgMdtStmHdr&& m) {
	this->metaDataStreamHeader = std::move(m.metaDataStreamHeader);
	m.metaDataStreamHeader = nullptr;
	this->begin = m.begin;
	m.begin = nullptr;
	this->mode = m.mode;
	m.mode = ImageMode::File;

}
LPVOID ImgMdtStmHdr::GetBegin(){
	GUARD_GENTLE(begin==nullptr,nullptr) 
	return begin; }

MDStreamHeader ImgMdtStmHdr::read() {
	MDStreamHeader md;
	ZeroMemory(&md, sizeof(MDStreamHeader));
	GUARD_GENTLE(begin == nullptr, md)
	memcpy(&md, this->metaDataStreamHeader, sizeof(MDStreamHeader));
	return md;
}


DWORD ImgMdtStmHdr::write(MDStreamHeader& md, HANDLE hProcess) {
	ASSERT_ADDR(begin)
	if (mode == ImageMode::File) {
		memcpy(this->metaDataStreamHeader, &md, sizeof(MDStreamHeader));
	}else if (mode == ImageMode::Memory) {
		ASSERT_HANDLE(hProcess)
		SIZE_T size;
		WriteProcessMemory(hProcess,begin,&md,sizeof(MDStreamHeader),size)
		memcpy(this->metaDataStreamHeader, &md, sizeof(MDStreamHeader));
	}
	return 0;
}

DWORD ImgMdtStmTableMgr::init(LPVOID lpBase, ULONGLONG mask, vector<DWORD*> size, ImageMode mode, HANDLE hProcess) {
	DWORD index = 0;
	/*for (ULONGLONG i = 0; i < ImageMetaDataTableStreamMaskArrayLen;i++) {
		if ((mask & ImageMetaDataTableStreamMaskArray[i]) == ImageMetaDataTableStreamMaskArray[i]) {
			metaDataTableArray.push_back(::CreateTableInstance(i));
			metaDataTableArray[i]->init(lpBase, *(size[index]), ImageMetaDataTableStreamMaskArray[i]);
			GetNextTable(lpBase, metaDataTableArray[i])
		}
	}*//*
	if ((mask & ImgMdtStmMask::Method) == ImgMdtStmMask::Method) {
		metaDataTableArray.push_back(::CreateTableInstance(6));
		DWORD result=metaDataTableArray[0]->init(GetMethodTable(lpBase), *(size[4]), ImgMdtStmMaskArray[6],mode,hProcess);
		if (result != 0) {
			return result;
		}
	}
	return 0;
}

ImgMdtStmTableMgr::~ImgMdtStmTableMgr() {
	if (this->metaDataTableArray.size() != 0) {
		for (auto i : metaDataTableArray) {
			if (i != nullptr) {
				delete i;
				i = nullptr;
			}	
		}
	}
	
}


DWORD ImgMdtStmMgr::init(LPVOID lpBase, ImageMode mode, HANDLE hProcess) {
	ASSERT_ADDR(lpBase);
	this->begin = lpBase;
	this->mode = mode;
	if (mode == ImageMode::Memory) {
		ASSERT_HANDLE(hProcess)
	}
	DWORD result = 0;
	result=metaDataStreamHeader.init(lpBase, mode, hProcess);
	if (result != 0) {
		return result;
	}
	lpBase = LPVOID((DWORD)lpBase + ImgMdtStmHdr::GetSize());
	DWORD count = GetCountFormMask(metaDataStreamHeader.read().MaskValid);
	for (DWORD i = 0; i < count; i++) {
		if (mode == ImageMode::File) {
			//初始化各个表的记录数
				lenArray.push_back((DWORD*)lpBase);
				
		}
		else if(mode==ImageMode::Memory)
		{
			SIZE_T size;
			lenArray.push_back(new DWORD);
			ReadProcessMemory(hProcess, lpBase, lenArray[i], sizeof(DWORD), &size);

		}
		lpBase = LPVOID((DWORD)lpBase + 4);
	}
	
	
	result=metaDataStreamTableManager.init(lpBase, metaDataStreamHeader.read().MaskValid,lenArray,mode,hProcess);
	if (result != 0) {
		return result;
	}
	return 0;
}


ImgMdtStmMgr::ImgMdtStmMgr(ImgMdtStmMgr& m):metaDataStreamHeader(m.metaDataStreamHeader)
, metaDataStreamTableManager(m.metaDataStreamTableManager){
	std::copy(m.lenArray.begin(), m.lenArray.end(), this->lenArray.begin());
	this->mode = m.mode;
	this->begin = m.begin;

}

ImgMdtStmMgr::ImgMdtStmMgr(ImgMdtStmMgr&& m) : metaDataStreamHeader(std::move(m.metaDataStreamHeader)),
metaDataStreamTableManager(std::move(m.metaDataStreamTableManager)) {
	m.lenArray = std::move(m.lenArray);
	this->mode = m.mode;
	this->begin = m.begin;
	m.begin = nullptr;
}

ImgMdtStmMgr::~ImgMdtStmMgr() {

}*/
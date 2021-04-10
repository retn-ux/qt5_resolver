#include "pch.h"
#include <CorAux.h>
#include <CorHdrEx.h>



/*

DWORD ImgStoreSigEx::init(LPVOID lpBaseAddress, ImageMode mode, HANDLE hProcess) {
	ASSERT_ADDR(lpBaseAddress)
	this->begin = lpBaseAddress;
	this->mode = mode;
	if (mode == ImageMode::File) {
		this->ss = (STORAGESIGNATURE*)lpBaseAddress;
		VersionString = (char*)((DWORD)lpBaseAddress + sizeof(STORAGESIGNATURE));
	}
	else if (mode == ImageMode::Memory) {
		this->ss = new STORAGESIGNATURE;
		ASSERT_HANDLE(hProcess)
		SIZE_T size;
		ReadProcessMemory(hProcess, lpBaseAddress, ss, sizeof(STORAGESIGNATURE), size)
		this->VersionString = new char[ss->iVersionString];
		size = 0;
		ReadProcessMemory(hProcess, (LPVOID)((DWORD)lpBaseAddress + sizeof(STORAGESIGNATURE)), this->VersionString, ss->iVersionString, size);
	}
	
	return 0;
}

bool ImgStoreSigEx::IsTrue() {
	GUARD_GENTLE(this->ss==nullptr,false)
	return this->ss->ISignature == this->cTextSignatrue ? true : false;
}

dynamic::Image::STORAGESIGNATUREEX dynamic::Image::ImgStoreSigEx::GetHeader() {
	GUARD_GENTLE(this->ss==nullptr, STORAGESIGNATUREEX())
	return STORAGESIGNATUREEX(this->ss, this->VersionString);
}

DWORD ImgStoreSigEx::write(STORAGESIGNATUREEX ex, HANDLE hProcess) {
	if (begin == nullptr) {
		return ADDR_ERROR;
	}
	if (this->VersionString == nullptr && ss==nullptr) {
		return ADDR_ERROR;
	}
	if (this->mode == ImageMode::File) {
		memcpy(this->ss, &ex, sizeof(STORAGESIGNATURE));
		if (ex.header.iVersionString > this->ss->iVersionString) {
			return SIZE_TO_LOW;
		}
		memcpy(this->VersionString, &ex.VersionString, ex.header.iVersionString);
	}
	else if (this->mode == ImageMode::Memory) {
		ASSERT_HANDLE(hProcess)
		SIZE_T size;
		WriteProcessMemory(hProcess,begin,&ex,sizeof(STORAGESIGNATURE),size)
		if (ex.header.iVersionString > this->ss->iVersionString) {
			return SIZE_TO_LOW;
		}
		WriteProcessMemory(hProcess, LPVOID((DWORD)begin + sizeof(STORAGESIGNATURE)), &ex.VersionString, ex.header.iVersionString, size);
		memcpy(this->ss, &ex, sizeof(STORAGESIGNATURE));
		memcpy(this->VersionString, &ex.VersionString, ex.header.iVersionString);
	}
	return 0;
}

ImgStoreSigEx::~ImgStoreSigEx() {
	if (this->mode == ImageMode::Memory&& this->ss != nullptr) {
		delete this->ss;
		this->ss = nullptr;
	}
}

DWORD ImgStoreHdrEx::init(LPVOID lpBaseAddress, ImageMode mode, HANDLE hProcess) {
	if (lpBaseAddress == nullptr) {
		return ADDR_ERROR;
	}
	this->mode = mode;
	this->begin = lpBaseAddress;
	if (this->mode == ImageMode::File) {
		storh = (STORAGEHEADER*)lpBaseAddress;
	}
	else if (this->mode == ImageMode::Memory) {
		this->storh = new STORAGEHEADER();
		ASSERT_HANDLE(hProcess)
		SIZE_T size;
		ReadProcessMemory(hProcess,lpBaseAddress,storh,GetSize(),size)
	}
	return 0;
}

STORAGEHEADER ImgStoreHdrEx::GetHeader() {
	STORAGEHEADER sg;
	if (this->storh != nullptr) {
		memcpy(&sg, this->storh, sizeof(STORAGEHEADER));
	}
	return sg;
}

DWORD ImgStoreHdrEx::write(STORAGEHEADER& header, HANDLE hProcess) {
	if (begin == nullptr) {
		return ADDR_ERROR;
	}
	if (storh == nullptr) {
		return UNINITIALIZED;
	}
	if (this->mode == ImageMode::File) {
		memcpy(this->storh, &header, sizeof(STORAGEHEADER));
	}
	else if (this->mode == ImageMode::Memory) {
		ASSERT_HANDLE(hProcess)
		SIZE_T size;
		WriteProcessMemory(hProcess,begin,&header,sizeof(STORAGEHEADER),size)
		memcpy(this->storh, &header, sizeof(STORAGEHEADER));
	}
	return 0;
}


ImgStoreHdrEx::~ImgStoreHdrEx() {
	if (this->mode == ImageMode::Memory&&this->storh!=nullptr) {
		delete this->storh;
		this->storh = nullptr;
	}
}

ImgStoreStmHdr::ImgStoreStmHdr(ImgStoreStmHdr&& sg) {
	this->storsex = std::move(sg.storsex);
	this->begin = sg.begin;
	sg.begin = nullptr;
	this->mode = sg.mode;

}

ImgStoreStmHdr::ImgStoreStmHdr(ImgStoreStmHdr& sg) {
	std::copy(sg.storsex.begin(), sg.storsex.end(), this->storsex.begin());
	this->begin = sg.begin;
	this->mode = sg.mode;
}

DWORD ImgStoreStmHdr::init(LPVOID lpBaseAddress, USHORT number, ImageMode mode, HANDLE hProcess) {
	if (lpBaseAddress == nullptr) {
		return ADDR_ERROR;
	}
	STORAGESTREAMEX temp;
	ZeroMemory(&temp, sizeof(temp));
	this->mode = mode;
	this->begin = begin;
	for (USHORT i = 0; i < number; i++) {
		storsex.push_back(temp);
		if (this->mode == ImageMode::File) {
			storsex[i].stors = (STORAGESTREAM*)lpBaseAddress;
			storsex[i].rcName = (char*)(LPVOID((DWORD)lpBaseAddress + sizeof(STORAGESTREAM)));
			if (storsex[i].rcName[0] == '\0') {
				storsex[i].rcNameSize = 0;
			}
			else {
				for (DWORD d = 1; d <= 8; d++) {
					if (storsex[i].rcName[d * 4 - 1] == '\0') {
						storsex[i].rcNameSize = d * 4;
						break;
					}
				}
			}
		}
		else if (this->mode == ImageMode::Memory) {
			storsex[i].stors = new STORAGESTREAM;
			char buffer[4];
			storsex[i].rcName = nullptr;
			LPVOID rcNameBegin = (LPVOID((DWORD)lpBaseAddress + sizeof(STORAGESTREAM)));

			ASSERT_HANDLE(hProcess)
			SIZE_T size;
			//读取元数据流的头结构
			ReadProcessMemory(hProcess,lpBaseAddress,storsex[i].stors,sizeof(STORAGESTREAM),size)
			ReadProcessMemory(hProcess,lpBaseAddress,buffer,sizeof(buffer),size)
			if (buffer[0] == '\0') {
				storsex[i].rcNameSize = 0;
			}
			else {
				for (DWORD d = 1; d <= 8; d++) {
						if (buffer[3] == '\0') {
							storsex[i].rcNameSize = d * 4;
							break;
						}
						ReadProcessMemory(hProcess, LPVOID((DWORD)rcNameBegin + d * 4 - 1), buffer, sizeof(buffer), size)
				}
				storsex[i].rcName = new char[storsex[i].rcNameSize];
				ReadProcessMemory(hProcess, rcNameBegin, storsex[i].rcName, storsex[i].rcNameSize,size)
			}

		}
		
		
		lpBaseAddress = LPVOID((DWORD)lpBaseAddress + sizeof(ULONG) * 2 + storsex[i].rcNameSize);
	}

	return 0;

}

STORAGESTREAMEX dynamic::Image::ImgStoreStmHdr::Search(DWORD index) {
	return storsex[index - 1];
}

DWORD ImgStoreStmHdr::write(STORAGESTREAMEX storsex, DWORD index, HANDLE hProcess) {
	if (begin == nullptr) {
		return ADDR_ERROR;
	}
	if (this->storsex.size()==0) {
		return UNINITIALIZED;
	}
	if (this->mode == ImageMode::File) {
		this->storsex[index - 1].rcNameSize = storsex.rcNameSize;
		memcpy(this->storsex[index-1].stors, &storsex.stors, sizeof(STORAGEHEADER));	
		if (storsex.rcNameSize > storsex.rcNameSize) {
			return SIZE_TO_LOW;
		}
		memcpy(this->storsex[index - 1].rcName, &storsex.rcName, storsex.rcNameSize);
	}
	else if (this->mode == ImageMode::Memory) {
		ASSERT_HANDLE(hProcess)
		SIZE_T size;
		WriteProcessMemory(hProcess, begin, &storsex.stors, sizeof(STORAGEHEADER), size)
		if (storsex.rcNameSize > storsex.rcNameSize) {
			return SIZE_TO_LOW;
		}
		LPVOID start = LPVOID((DWORD)begin + sizeof(STORAGEHEADER));
		WriteProcessMemory(hProcess,start, &storsex.rcName,storsex.rcNameSize,size)
		memcpy(this->storsex[index - 1].rcName, &storsex.rcName, storsex.rcNameSize);
		memcpy(this->storsex[index - 1].stors, &storsex.stors, sizeof(STORAGEHEADER));
	}
	return 0;









}

ImgStoreStmHdr::~ImgStoreStmHdr() {
	if (this->mode == ImageMode::Memory && this->storsex.size() != 0) {
		for (auto i : this->storsex) {
			if (i.stors != nullptr ) {
				delete i.stors;
				i.stors = nullptr;
			}
			if (i.rcName != nullptr) {
				delete i.rcName;
				i.rcName = nullptr;
			}
		}
	}
}

int ImgCor20EmtEx::init(LPVOID lpBase, ImageMode mode, HANDLE hProcess) {
	
	DWORD result = 0;
	result = stros.init(lpBase, mode, hProcess);
	
	if (result != 0) {
		return result;
	}
	GUARD_GENTLE(stros.IsTrue(), ADDR_ERROR);
	GetNext(lpBase, stros)
	result=stroh.init(lpBase,mode,hProcess);
	GUARD_GENTLE(result == 0,result)
	GetNext(lpBase, stroh)
	result = imageStro.init(lpBase,stroh.GetHeader().iStream,mode,hProcess);
	if (result != 0) {
		return result;
	}
	DWORD offset = 0;
	
	for (int i = 1; i <= stroh.GetHeader().iStream; i++) {
		if (!strcmp(imageStro.Search(i).rcName,IMAGE_MDT_STREAM_SIGNATRUE) || !strcmp(imageStro.Search(i).rcName,IMAGE_MDT_STREAM_SIGNATRUE_COMPRESSION)) {
			offset = imageStro.Search(i).stors->iOffset;
			break;
		}
	}
	if (offset == 0) {
		return NOT_FOUND_MDT_TABLE_STREAM;
	}
	LPVOID mr = stros.GetBegin();
	LPVOID begin=LPVOID((DWORD)mr + offset);
	result=mdtStreanManager.init(begin,mode,hProcess);
	if (result != 0) {
		return result;
	}
	return 0;
}*/
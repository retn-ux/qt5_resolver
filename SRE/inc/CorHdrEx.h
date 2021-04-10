#pragma once

#include <vector>
#include <sredefs.h>
#include <ImageDefs.h>
#include <CorTableMgr.h>
using std::vector;

/*

using dynamic::Image::ImgMdtStmMgr;

struct STORAGESIGNATURE {
	ULONG ISignature;
	USHORT iMajorVer;
	USHORT iMinorVer;
	ULONG iExtraData;
	ULONG iVersionString;
};

struct STORAGESIGNATUREEX {
	STORAGESIGNATURE header;
	char* VersionString;
	STORAGESIGNATUREEX() :VersionString(nullptr) {
		memset(&header, 0, sizeof(header));
	}
	STORAGESIGNATUREEX(STORAGESIGNATURE *header, char* VersionString) :VersionString(nullptr) {
		memcpy(&this->header, header, sizeof(STORAGESIGNATURE));
		VersionString = new char[header->iVersionString];
		if (VersionString != nullptr) {
			memcpy(this->VersionString, VersionString, header->iVersionString);
		}
		
	}
	~STORAGESIGNATUREEX() {
		delete VersionString;
	}
};




struct ImgStoreSigEx {
private:
	const DWORD cTextSignatrue = 0x424A5342;
	STORAGESIGNATURE* ss;
	LPVOID begin;
	ImageMode mode;
	char* VersionString;
public:
	DWORD init(LPVOID lpBaseAddress,ImageMode mode,HANDLE hProcess=nullptr);
	bool IsTrue();
	DWORD GetSize() { return sizeof(STORAGESIGNATURE)+ss->iVersionString; }
	STORAGESIGNATUREEX GetHeader();
	DWORD write(STORAGESIGNATUREEX ex, HANDLE hProcess = nullptr);
	LPVOID GetBegin() { return begin; };
	~ImgStoreSigEx();
};

struct STORAGEHEADER {
	byte fFlags;
	byte pad;
	USHORT iStream;			//流的数量
};

class ImgStoreHdrEx {
private:
	STORAGEHEADER* storh;
	LPVOID begin;
	ImageMode mode;
public:
	DWORD init(LPVOID lpBaseAddress,ImageMode mode,HANDLE hProcess=nullptr);
	static DWORD GetSize() { return sizeof(STORAGEHEADER); }
	DWORD write(STORAGEHEADER& header, HANDLE hProcess = nullptr);
	STORAGEHEADER GetHeader();
	~ImgStoreHdrEx();
};
struct STORAGESTREAM {
	ULONG iOffset;
	ULONG iSize;
};

struct STORAGESTREAMEX {
	STORAGESTREAM* stors;
	char* rcName;
	DWORD rcNameSize;  //自定义不属于头结构
};

struct ImgStoreStmHdr {
private:
	vector<STORAGESTREAMEX> storsex;
	LPVOID begin;
	ImageMode mode;
public:
	ImgStoreStmHdr() {};
	ImgStoreStmHdr(ImgStoreStmHdr&& sg);
	ImgStoreStmHdr(ImgStoreStmHdr& sg);
	DWORD init(LPVOID lpBaseAddress, USHORT number, ImageMode mode, HANDLE hProcess = nullptr);
	LPVOID GetBegin() { return begin; }
	STORAGESTREAMEX Search(DWORD index);
	DWORD write(STORAGESTREAMEX storsex, DWORD index, HANDLE hProcess = nullptr);
	~ImgStoreStmHdr();
};









	
class ImgCor20EmtEx {
		
	
	ImgStoreSigEx stros;				//元数据储存签名
	ImgStoreHdrEx stroh;				//元数据储存头	
	ImgStoreStmHdr imageStro;		//元数据流头
	ImgMdtStmMgr mdtStreanManager;
public:
	ImgCor20EmtEx() {}
	int init(LPVOID lpBase,ImageMode mode,HANDLE hProcess=nullptr);
	ImgStoreSigEx GetStrorageSignatrueEx() { return stros; }
	ImgStoreHdrEx GetStrorageHeaderEx() { return stroh; }
	ImgStoreStmHdr GetStrorageStreamHeaderEx() { return imageStro; }
	ImgMdtStmMgr GetMetaDataStreamManager() { return mdtStreanManager; }
	};
*/
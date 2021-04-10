#pragma once
#include <vector>
#include <string>
#include <sredefs.h>
#include <CorHdr.h>
#include <ImageDefs.h>
using std::vector;
using std::string;






/*
typedef IMAGE_COR_ILMETHOD ImgMdtMethodHdr;
typedef IMAGE_COR_ILMETHOD_TINY ImgMdtMethodTinyHdr;
typedef IMAGE_COR_ILMETHOD_FAT ImgMdtMethodFatHdr;
//function
struct IImgMdtTable;
DWORD GetCountFormMask(ULONGLONG mask);
LPVOID GetMethodTable(LPVOID begin);
IImgMdtTable* CreateTableInstance(DWORD index);


//struct
struct MDStreamHeader {
	DWORD Reserved;
	byte Major;
	byte Minjor;
	byte Heaps;
	byte Rid;
	ULONGLONG MaskValid;
	ULONGLONG Sorted;

};

struct MDTMethod {
	DWORD RVA;
	WORD ImplFlags;
	WORD Flags;
	WORD Name;
	WORD Signatrue;
	WORD ParmaList;
};

//class

class IImgMdtTable {
protected:
	ULONGLONG mask;
	LPVOID begin;
	ImageMode mode;
public:
	IImgMdtTable() :mask(0), begin(nullptr), mode(ImageMode::File) {}
	virtual DWORD init(LPVOID base, DWORD size, ULONGLONG mask, ImageMode mode, HANDLE hProcess = nullptr) = 0;
	virtual Gauge GetTableSize() = 0;
	~IImgMdtTable() {};
};


class ImgMdtStmHdr {
private:
	MDStreamHeader* metaDataStreamHeader;
	LPVOID begin;
	ImageMode mode;
public:
	ImgMdtStmHdr() {}
	DWORD init(LPVOID lpBaseAddress, ImageMode mode, HANDLE hProcess = nullptr);
	~ImgMdtStmHdr() {
		if (metaDataStreamHeader != nullptr && mode == ImageMode::Memory)
			delete metaDataStreamHeader;
		metaDataStreamHeader = nullptr;
	}
	ImgMdtStmHdr(ImgMdtStmHdr& m);
	ImgMdtStmHdr(ImgMdtStmHdr&& m);
	static DWORD GetSize() { return sizeof(MDStreamHeader); }
	LPVOID GetBegin();
	MDStreamHeader read();
	DWORD write(MDStreamHeader& md, HANDLE hProcess = nullptr);
};

		
class ImgMdtMethodTableEx :public IImgMdtTable {
private:
	vector<MDTMethod*> metaDataMethodTable;
public:
	ImgMdtMethodTableEx() {}
	ImgMdtMethodTableEx(ImgMdtMethodTableEx&& m);
	ImgMdtMethodTableEx(ImgMdtMethodTableEx& m);
	DWORD init(LPVOID base, DWORD size, ULONGLONG mask, ImageMode mode, HANDLE hProcess = nullptr) override;
	MDTMethod GetMethodTable(DWORD index);
	DWORD write(MDTMethod& md, DWORD index, HANDLE hProcess = nullptr);
	Gauge GetTableSize() override { return sizeof(MDTMethod) * (this->metaDataMethodTable.size() + 1); };
	DWORD GetSize() { return sizeof(DWORD) + sizeof(WORD) * 5; };
	~ImgMdtMethodTableEx();
};



class ImgMdtStmTableMgr {
		vector<IImgMdtTable*> metaDataTableArray;
	public:
		ImgMdtStmTableMgr() {};
		ImgMdtStmTableMgr(ImgMdtStmTableMgr&& m) {
			this->metaDataTableArray = std::move(m.metaDataTableArray);
		}
		ImgMdtStmTableMgr(ImgMdtStmTableMgr& m) {
			std::copy(m.metaDataTableArray.begin(), m.metaDataTableArray.end(), this->metaDataTableArray.begin());
		}
		DWORD init(LPVOID lpBase, ULONGLONG mask, vector<DWORD*> size, ImageMode mode, HANDLE hProcess = nullptr);

		IImgMdtTable GetTable(DWORD index);
		~ImgMdtStmTableMgr();
};



class ImgMdtStmMgr {
private:
	ImgMdtStmHdr metaDataStreamHeader;		//元数据表流的头结构
	vector<DWORD*> lenArray;									//表中记录的个数
	ImgMdtStmTableMgr metaDataStreamTableManager;		//元数据表管理
	ImageMode mode;
	LPVOID begin;
public:
	DWORD init(LPVOID lpBase, ImageMode mode, HANDLE hProcess = nullptr);
	ImgMdtStmMgr() {}
	ImgMdtStmMgr(ImgMdtStmMgr& m);
	ImgMdtStmMgr(ImgMdtStmMgr&& m);
	~ImgMdtStmMgr();
};
		*/

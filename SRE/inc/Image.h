#pragma once

#include <vector>
#include <string>
#include <sredefs.h>
#include <ImageDefs.h>
#include <CorHdrEx.h>
#include <CorHdr.h>
using std::string;
using std::vector;



//function
dword Alignment(dword size, dword granularity);
class IImgHdr {
protected:
	void_ptr begin;
public:
	IImgHdr(void_ptr start) :begin(begin) {};
	virtual bool init(void_ptr start, HANDLE hProcess) = 0;
	virtual void_ptr Begin() = 0;
};

//class
class ImgDdrEx :public IImgHdr {
private:
	IMAGE_DOS_HEADER idh;

public:
	static const word stdMzSign = 0x5A4D;
public:
	ImgDdrEx();
	bool IsTrue();
	IMAGE_DOS_HEADER read(void);
	void_ptr Begin() override { return begin; };
	static size_t Size() { return sizeof(IMAGE_DOS_HEADER); };
	bool init(void_ptr start, HANDLE hProcess = nullptr) override;
	bool write(IMAGE_DOS_HEADER& header, HANDLE hProcess = nullptr);
	~ImgDdrEx();
};

class ImgFdrEx : public IImgHdr {
private:
	IMAGE_FILE_HEADER ifh;
public:
	ImgFdrEx();
	IMAGE_FILE_HEADER read();
	void_ptr Begin() override { return begin; };
	static size_t Size() { return sizeof(IMAGE_FILE_HEADER); }
	bool init(void_ptr lpBase, HANDLE hProcess = nullptr) override;
	bool write(IMAGE_FILE_HEADER& header, HANDLE hProcess = nullptr);
	~ImgFdrEx();
};

class ImgOHdrEx : public IImgHdr {
private:
	IMAGE_OPTIONAL_HEADER ioh;
public:
	ImgOHdrEx();
	IMAGE_OPTIONAL_HEADER read(void);
	void_ptr Begin() override { return begin; };
	IMAGE_DATA_DIRECTORY SearchDataDirectory(byte index);
	static size_t Size() { return sizeof(IMAGE_OPTIONAL_HEADER); }
	bool init(void_ptr lpBase, HANDLE hProcess = nullptr) override;
	bool write(IMAGE_OPTIONAL_HEADER& header, HANDLE hProcess = nullptr);
	~ImgOHdrEx();
};

class ImgNdrEx : public IImgHdr {
private:
	DWORD sign;
	ImgFdrEx fileh;
	ImgOHdrEx optionalh;
public:
	static const DWORD stdSignture = 0x4550;
public:
	ImgNdrEx();
	bool IsTrue();
	void_ptr Begin() override;
	ImgOHdrEx GetOdrEx();
	ImgFdrEx GetFdrEx();
	IMAGE_NT_HEADERS read(void);
	static size_t Size() { return sizeof(IMAGE_NT_HEADERS); };
	bool write(IMAGE_NT_HEADERS& header, HANDLE hProcess = nullptr);
	bool init(void_ptr lpBase, HANDLE hProcess = nullptr) override;
};

class ImgSdrEx{
private:
	vector<IMAGE_SECTION_HEADER>ish;
	void_ptr begin;
public:
	ImgSdrEx(){}
	bool init(void_ptr lpBaseAddress, Gauge number, HANDLE hProcess = nullptr);
	size_t Amount() { return ish.size(); }
	void_ptr Begin() { return begin; }
	Gauge where(void_ptr addr);
	IMAGE_SECTION_HEADER read(Gauge index);
	IMAGE_SECTION_HEADER read(string name);
	bool write(IMAGE_SECTION_HEADER& section, Gauge index, HANDLE hProcess = nullptr);
	bool write(IMAGE_SECTION_HEADER& section, string name, HANDLE hProcess = nullptr);
	bool AddToList(IMAGE_SECTION_HEADER& sh);			//将节表加入到管理队列中并不会改变内存
	size_t Size() { return sizeof(IMAGE_SECTION_HEADER) * (ish.size()); }
	~ImgSdrEx();
};

class ImgCor20Hdr :public IImgHdr  {
private:
	IMAGE_COR20_HEADER cor20_header;
public:
	ImgCor20Hdr();
	void_ptr Begin()override { return this->begin; };
	bool init(void_ptr addr , HANDLE hProcess = nullptr) override;
	static size_t Size() { return sizeof(IMAGE_COR20_HEADER); }
	IMAGE_COR20_HEADER read();
	bool write(IMAGE_COR20_HEADER& corh, HANDLE hProcess = nullptr);
	~ImgCor20Hdr();
};



class Image {
private:
	bool inMemory;
	LPVOID mImageBaseAddress;
	ImgDdrEx dosh;
	ImgNdrEx nth;
	ImgSdrEx sectionh;
	/*ImgCor20Hdr corh;					//COR
	ImgCor20EmtEx corElement;*/
public:

	Image();
	bool init(void_ptr lpBaseAddress, bool inMemory, HANDLE hProcess = nullptr);
	Gauge rtof(Gauge addr);
	Gauge ftor(Gauge addr);
	bool IsCorFile();

	ImgDdrEx GetDHdr() { return dosh; };
	ImgNdrEx GetNHdr() { return nth; };
	ImgSdrEx GetSHdr() { return sectionh; };
	/*ImgCor20Hdr GetCor20Hdr() { return corh; };
	ImgCor20EmtEx GetCor20Emt() { return corElement; };*/
	int AddSectionHeader(string section_name, dword size, DWORD attri, IMAGE_SECTION_HEADER* out_section);
	int ChangeHeaderToExtendLastSection(dword size);
	size_t GetImgHdrSize() { return dosh.read().e_lfanew + nth.Size() + sectionh.Size(); };
};

dword AddSectionToFile(string file_name,string section_name, dword size, dword attri);

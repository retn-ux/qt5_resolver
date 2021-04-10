#include "pch.h"
#include <file.h>
#include <MathPlus.h>
#include <SREMemory.h>
#include <Image.h>




dword Alignment(dword size, dword granularity) {
	GUARD_GENTLE(granularity != 0, 0);
	dword multiple = size / granularity;
	if ((size % granularity) != 0) {
		multiple++;
	}
	return multiple * granularity;
}



ImgDdrEx::ImgDdrEx() :IImgHdr(nullptr) {
	memset(&idh, 0, sizeof(idh));
}


bool ImgDdrEx::init(void_ptr start, HANDLE hProcess){
	GUARD_GENTLE(ReadMemory(start, &idh, sizeof(idh), hProcess), false);
	this->begin = start;
	return true;
}

ImgDdrEx::~ImgDdrEx() {
}

IMAGE_DOS_HEADER ImgDdrEx::read(void) {
	return idh;
	
}

bool ImgDdrEx::write(IMAGE_DOS_HEADER &header,HANDLE hProcess) {
	GUARD_GENTLE(WriteMemory(begin, &header,sizeof(header), hProcess), false);
	this->idh = header;
	return true;
}


bool ImgDdrEx::IsTrue() {
	if (stdMzSign == idh.e_magic) {
		return true;
	}
	return false;
}


ImgFdrEx::ImgFdrEx():IImgHdr(nullptr)  {
	memset(&ifh, 0, sizeof(ifh));
};

bool ImgFdrEx::init(void_ptr lpBase, HANDLE hProcess) {
	GUARD_GENTLE(ReadMemory(lpBase, &this->ifh, sizeof(ifh), hProcess), false);
	this->begin = lpBase;
	return true;
}

IMAGE_FILE_HEADER ImgFdrEx::read() {
		return ifh;
}

bool ImgFdrEx::write(IMAGE_FILE_HEADER& header, HANDLE hProcess) {
	GUARD_GENTLE(WriteMemory(begin, &header, sizeof(header), hProcess), false);
	this->ifh = header;
	return true;
}



ImgFdrEx::~ImgFdrEx() {
}


ImgOHdrEx::ImgOHdrEx() :IImgHdr(nullptr) {
	memset(&ioh, 0, sizeof(ioh));
}



bool ImgOHdrEx::init(void_ptr lpBase, HANDLE hProcess) {
	GUARD_GENTLE(ReadMemory(lpBase, &ioh, sizeof(ioh), hProcess), false);
	this->begin = lpBase;
	return true;
}

IMAGE_OPTIONAL_HEADER ImgOHdrEx::read() {
	GUARD_GENTLE(this->begin != nullptr, IMAGE_OPTIONAL_HEADER());
	return ioh;

}

IMAGE_DATA_DIRECTORY ImgOHdrEx::SearchDataDirectory(byte index) {
	GUARD_GENTLE(index <= 16, IMAGE_DATA_DIRECTORY());
	return ioh.DataDirectory[index - 1];
}


bool ImgOHdrEx::write(IMAGE_OPTIONAL_HEADER& header, HANDLE hProcess) {
	GUARD_GENTLE(WriteMemory(begin, &header, sizeof(header), hProcess), false);
	this->ioh = header;
	return true;
}

ImgOHdrEx::~ImgOHdrEx() {
}


ImgNdrEx::ImgNdrEx():IImgHdr(nullptr) {
	sign = 0;
}


bool ImgNdrEx::init(void_ptr lpBase, HANDLE hProcess) {
	GUARD_GENTLE(ReadMemory(lpBase, &sign, sizeof(sign), hProcess), false);
	GUARD_GENTLE(fileh.init(LPVOID((Gauge)lpBase + 4), hProcess), false);
	GUARD_GENTLE(optionalh.init(LPVOID((Gauge)lpBase + 4 + fileh.Size()), hProcess), false);
	this->begin = lpBase;
	return true;
}

bool ImgNdrEx::IsTrue() {
	if (sign == stdSignture) {
		return true;
	}
	return false;
}

IMAGE_NT_HEADERS ImgNdrEx::read(void) {
	
	IMAGE_NT_HEADERS py;
	py.Signature = this->sign;
	py.FileHeader = fileh.read();
	py.OptionalHeader = optionalh.read();
	return py;
}

ImgOHdrEx ImgNdrEx::GetOdrEx() {
	return optionalh;
}

ImgFdrEx ImgNdrEx::GetFdrEx() { return fileh; }

LPVOID ImgNdrEx::Begin() { return begin; }

bool ImgNdrEx::write(IMAGE_NT_HEADERS &header, HANDLE hProcess) {
	GUARD_GENTLE(WriteMemory(begin, &header.Signature, sizeof(header.Signature), hProcess), false);
	GUARD_GENTLE(this->fileh.write(header.FileHeader, hProcess), false);
	GUARD_GENTLE(this->optionalh.write(header.OptionalHeader, hProcess), false);
	return true;
}


bool ImgSdrEx::init(void_ptr lpBaseAddress, Gauge number, HANDLE hProcess) {
	bool result = true;
	this->begin = lpBaseAddress;
	for (Gauge i = 0; i < number; i++) {
		ish.push_back(IMAGE_SECTION_HEADER());
		bool r = ReadMemory(lpBaseAddress, &ish[i], sizeof(IMAGE_SECTION_HEADER), hProcess);
		if (result == true && r == false) {
			result = r;
			this->begin = nullptr;
		}
		lpBaseAddress = void_ptr((Gauge)lpBaseAddress + sizeof(IMAGE_SECTION_HEADER));
	}
	
	return result;
}


Gauge ImgSdrEx::where(void_ptr addr) {
	GUARD_ADDR(begin != nullptr, 0);
	GUARD_GENTLE(ish.size() != 0, 0);
	for (size_t d = 0; d < ish.size(); d++) {
		Gauge sectionBegin = ish[d].VirtualAddress;
		Gauge sectionEnd = ish[d].Misc.VirtualSize + sectionBegin;
		if (toGauge(addr) >= sectionBegin && toGauge(addr) < sectionEnd) {
			return d+1;
		}
	}
	return 0;
}

IMAGE_SECTION_HEADER ImgSdrEx::read(Gauge index) {
	
	IMAGE_SECTION_HEADER py;
	ZeroMemory(&py, sizeof(IMAGE_SECTION_HEADER));
	if (index > ish.size()||index==0||ish.size()==0||this->begin==nullptr) {
		return py;
	}
	memcpy(&py, &ish[index-1], sizeof(IMAGE_SECTION_HEADER));
	return py;
}

IMAGE_SECTION_HEADER ImgSdrEx::read(string name) {
	
	IMAGE_SECTION_HEADER py;
	ZeroMemory(&py, sizeof(IMAGE_SECTION_HEADER));
	GUARD_GENTLE(ish.size() != 0, py);
	GUARD_GENTLE(begin != nullptr ,py);
	for (size_t i = 0; i > this->ish.size(); i++) {
		if (!strcmp(name.c_str(), reinterpret_cast<char *>(ish[i].Name))) {
			return this->read(i + 1);
		}
	}

	return py;
}


bool ImgSdrEx::write(IMAGE_SECTION_HEADER& section, Gauge index, HANDLE hProcess) {
	if (index > ish.size() || index == 0) {
		return false;
	}
	if (this->begin == nullptr) {
		return false;
	}
	
	if (ish.size() == 0) {
		return false;
	}
	void_ptr start = vptr_add_Gauge(begin, sizeof(section) * (index - 1));
	GUARD_GENTLE(WriteMemory(start, &section, sizeof(section), hProcess), false);
	this->ish[index - 1] = section;
	return true;
}
bool ImgSdrEx::write(IMAGE_SECTION_HEADER& section, string name, HANDLE hProcess) {
	GUARD_GENTLE(this->begin != nullptr && ish.size() != 0, false);
	for (size_t i = 0; i > this->ish.size(); i++) {
		if (!strcmp(name.c_str(), reinterpret_cast<char*>(ish[i].Name))) {
			return this->write(section, i + 1, hProcess);
		}
	}
	return false;
}
bool ImgSdrEx::AddToList(IMAGE_SECTION_HEADER& sh) {
	GUARD_GENTLE(ish.size()!=0&&begin!=nullptr,false)
	this->ish.push_back(sh);
	return true;
}

ImgSdrEx::~ImgSdrEx() {
}


ImgCor20Hdr::ImgCor20Hdr():IImgHdr(nullptr) {
	memset(&cor20_header, 0, sizeof(cor20_header));
}

bool ImgCor20Hdr::init(void_ptr addr, HANDLE hProcess) {
	GUARD_GENTLE(ReadMemory(addr, &cor20_header, sizeof(cor20_header), hProcess), false);
	this->begin = addr;
	return true;
}


bool ImgCor20Hdr::write(IMAGE_COR20_HEADER& corh, HANDLE hProcess) {
	GUARD_GENTLE(WriteMemory(begin, &corh, sizeof(corh), hProcess), false);
	cor20_header = corh;
	return true;
}

IMAGE_COR20_HEADER ImgCor20Hdr::read() {
	GUARD_GENTLE(begin != nullptr, IMAGE_COR20_HEADER())
	return cor20_header;
}

ImgCor20Hdr::~ImgCor20Hdr() {

}

Image::Image():mImageBaseAddress(nullptr){}


bool Image::init(void_ptr addr,bool inMemory, HANDLE hProcess) {

	mImageBaseAddress = addr;
	this->inMemory = inMemory;
	GUARD_GENTLE(dosh.init(addr, hProcess), false);
	//初始化Dos头
	GUARD_GENTLE(dosh.IsTrue(), false);

	//初始化NT头
	LPVOID ntStart = vptr_add_Gauge(addr , dosh.read().e_lfanew);
	GUARD_GENTLE(this->nth.init(ntStart, hProcess), false);
	GUARD_GENTLE(this->nth.IsTrue(), false);

	//初始化节表头
	LPVOID lpSectionStart = vptr_add_Gauge(ntStart, this->nth.Size());
	GUARD_GENTLE(sectionh.init(lpSectionStart, this->nth.GetFdrEx().read().NumberOfSections, hProcess),false);
	
	//判断是否为Cor文件是的话初始化corh
	/*if (IsCorFile()) {
		LPVOID lpBase = 0;
		ImgOHdrEx mide = this->nth.GetOdrEx();
		if (!inMemory) {
			
			lpBase = vptr_add_Gauge(addr,this->rtof(mide.SearchDataDirectory(15).VirtualAddress));
		}
		else{
			lpBase = vptr_add_Gauge(addr,mide.SearchDataDirectory(15).VirtualAddress);
		}
		
		corh.init(lpBase,mode,hProcess);
		DWORD rva = corh.read().MetaData.VirtualAddress;
		DWORD va = 0;
		if (!inMemory) {
			va = this->rtof(rva) + (DWORD)mImageBaseAddress;
		}
		else{
			va = rva + (DWORD)mImageBaseAddress;
		}	
 		int result = corElement.init((LPVOID)va,mode,hProcess);
		if (result!=0) {
			return result;
		}
	}*/
	return true;
}


int Image::AddSectionHeader(string name, dword size, DWORD attri,IMAGE_SECTION_HEADER* out_section) {
	if (name.length() > IMAGE_SIZEOF_SHORT_NAME) {
		return NAME_TO_LONG;
	}

	size_t sizeNow = GetImgHdrSize();
	//section的getSize返回的是整个节表头的大小
	if ((nth.read().OptionalHeader.SizeOfHeaders - sizeNow) >= (sizeof(IMAGE_SECTION_HEADER))) {
		void_ptr newSectionHeaderBegin = vptr_add_Gauge(mImageBaseAddress,sizeNow);
		//初始化节表头
		IMAGE_SECTION_HEADER newHeader;
		ImgOHdrEx m = nth.GetOdrEx();
		IMAGE_OPTIONAL_HEADER optional = m.read();
		ZeroMemory(&newHeader, sizeof(IMAGE_SECTION_HEADER));
		memcpy(newHeader.Name, name.c_str(), name.length());
		newHeader.Characteristics = attri;
		newHeader.Misc.VirtualSize = Alignment(size, optional.SectionAlignment);
		
		
		//计算节表起始地址
		IMAGE_SECTION_HEADER last = sectionh.read(sectionh.Amount());
		newHeader.VirtualAddress = last.VirtualAddress+Alignment(last.Misc.VirtualSize,optional.SectionAlignment);
		//计算节表文件对齐大小
		newHeader.SizeOfRawData = Alignment(size,optional.FileAlignment);
		//计算节表在文件中的偏移
		newHeader.PointerToRawData = last.PointerToRawData + last.SizeOfRawData;
		//修正NT头中的数据
		IMAGE_NT_HEADERS nthb = this->nth.read();
		nthb.FileHeader.NumberOfSections += 1;
		if (nthb.OptionalHeader.SizeOfImage < (newHeader.VirtualAddress + size)) {
			nthb.OptionalHeader.SizeOfImage += newHeader.Misc.VirtualSize;
		}
		//添加到类的节管理向量中	
		bool result = this->nth.write(nthb);
		if (!result) {
			return WRITE_ERROR;
		}
		result=this->sectionh.AddToList(newHeader);
		GUARD_GENTLE(result, UNINIT);
		result=this->sectionh.write(newHeader, sectionh.Amount());
		GUARD_GENTLE(result, WRITE_ERROR);
		*out_section = newHeader;
		return 0;
	}
	return SIZE_TO_LOW;
}


int Image::ChangeHeaderToExtendLastSection(dword size) {
	GUARD_GENTLE(!inMemory, MODE_ERROR);
	IMAGE_SECTION_HEADER last_section = sectionh.read(sectionh.Amount());
	IMAGE_OPTIONAL_HEADER imge_odr = nth.GetOdrEx().read();
	dword file_size = Alignment(size, imge_odr.FileAlignment);
	dword memory_size = Alignment(size, imge_odr.SectionAlignment);
	last_section.SizeOfRawData += file_size;
	last_section.Misc.VirtualSize += memory_size;
	dword last_section_end = last_section.VirtualAddress + last_section.Misc.VirtualSize;
	if (last_section_end > imge_odr.SizeOfImage) {
		imge_odr.SizeOfImage = imge_odr.SizeOfImage + memory_size;
		if (!nth.GetOdrEx().write(imge_odr)) {
			return WRITE_ERROR;
		}
	}
	GUARD_GENTLE(sectionh.write(last_section, sectionh.Amount()), WRITE_ERROR);
	return 0;
	
}

Gauge Image::rtof(Gauge addr) {
	if (addr < nth.read().OptionalHeader.SizeOfHeaders) {
		return addr;
	}
	Gauge index = sectionh.where((LPVOID)addr);
	if (index == 0) {
		return 0;
	}
	IMAGE_SECTION_HEADER sh = sectionh.read(index);
	//计算偏移地址
	Gauge offset = addr - sh.VirtualAddress;
	return offset + sh.PointerToRawData;
}

Gauge Image::ftor(Gauge addr) {
	if (addr < nth.GetOdrEx().read().SizeOfHeaders) {
		return addr;
	}
	Gauge ret = 0;
	IMAGE_SECTION_HEADER this_sec;
	size_t num = sectionh.Amount();
	for (size_t i = 1; i <= num; i++) {
		this_sec = sectionh.read(i);
		Gauge sec_end=this_sec.PointerToRawData + this_sec.SizeOfRawData;
		if (addr >= this_sec.PointerToRawData || addr < sec_end) {
			Gauge offset = addr - this_sec.PointerToRawData;
			ret = offset + this_sec.VirtualAddress;
			break;
		}
	}
	return ret;
}


bool Image::IsCorFile() {
	return nth.GetOdrEx().SearchDataDirectory(15).VirtualAddress == 0 ? false : true;
}



dword AddSectionToFile(string file_name, string section_name, dword size, dword attri) {


	HANDLE map;
	dword result;
	HANDLE fileHandle = ::CreateFileA(file_name.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	void_ptr addr = CreateImageMapFile(fileHandle, 0, PAGE_READWRITE, FILE_MAP_ALL_ACCESS, map, &result);
	GUARD_GENTLE(addr != 0, result);
	Image img;
	GUARD_GENTLE(img.init(addr, false),0xFFFFFFFF);
	IMAGE_OPTIONAL_HEADER opt_header = img.GetNHdr().GetOdrEx().read();
	IMAGE_SECTION_HEADER last_section = img.GetSHdr().read(img.GetSHdr().Amount());
	IMAGE_SECTION_HEADER section_new;
	int ret=img.AddSectionHeader(section_name,size,attri,&section_new);
	GUARD_GENTLE(ret == 0, ret);
	GUARD_SEVERE(UnmapOfFile(addr, map));
	dword rett = SetFileSize(fileHandle, size, FILE_SIZE_ADD);
	if (rett != 0) {
		return ret;
	}
	return 0;
}


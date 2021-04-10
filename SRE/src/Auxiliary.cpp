#include "pch.h"
#include <Auxiliary.h>
#include <sstream>
#include <bitset>
#include <SREException.h>




vector<string> split(string org, string sep) {
	using std::copy;
	size_t index = 0;
	vector<string> ret;
	while (org.length()>0) {
		index = org.find(sep);
		string news;
		if (index != string::npos && index!=0) {
			news.resize(index + 1);
			copy(org.begin(), org.begin() + index, news.begin());
			ret.push_back(news);
		}
		else if(index==string::npos){
			ret.push_back(org);
			break;
		}
		org = org.erase(0, index + 1);

	}

	return ret;

}
Gauge stog(const string& s) {
	stringstream ss;
	ss <<hex<< s;
	Gauge ret;
	ss >> ret;
	return ret;
}



vector<string> CCharToString(char** ptr, size_t size) {
	vector<string> res;
	if (size == 0) {
		return res;
	}
	for (size_t i = 0; i < size; i++) {
		string str = ptr[i];
		res.push_back(str);
	}
	return res;
}



wstring FormatErrorMsgW(DWORD serial) {
	
	LPTSTR ErrorDispose = NULL;
	BOOL judge = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		serial,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&ErrorDispose,
		0,
		NULL
	);
	return ErrorDispose;
}

string WStrStr(wstring wstr) {
	string result;
	wchar_t* unicode = new wchar_t[(wstr.size() + 1)*2];
	GetDataFromWStr(wstr, unicode, wstr.size());
	if (unicode == nullptr) {
		return result;
	}
	BOOL valid= FALSE;
	int c_size = WideCharToMultiByte(CP_ACP, 0, unicode, -1, nullptr, 0,nullptr,&valid);
	GUARD_GENTLE(c_size != 0, result);
	GUARD_GENTLE(valid == FALSE, result);
	char* cstr = new char[c_size];
	int ret_sz = WideCharToMultiByte(CP_ACP, 0, unicode, -1, cstr, c_size,nullptr,&valid);
	GUARD_GENTLE(ret_sz != 0, result);
	GUARD_GENTLE(valid == FALSE, result);
	result = cstr;
	delete cstr;
	delete unicode;
	return result;
}


wstring StrWStr(string str) {
	wstring result;
	int w_size=MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr,0);
	GUARD_GENTLE(w_size != 0, result);
	wchar_t *wstr = new wchar_t[w_size];
	int ret_sz=MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr, w_size);
	GUARD_GENTLE(ret_sz != 0, result);
	result = wstr;
	delete[] wstr;

	return result;
}

void GetDataFromStr(string str, char* data, size_t size) {
	if (str.size() == 0) {
		data = nullptr;
		return;
	}
	memcpy(data, str.c_str(), size);

}


void GetDataFromWStr(wstring str,wchar_t* data, size_t size) {
	if (str.size() == 0) {
		data = nullptr;
		return;
	}
	memcpy(data, str.c_str(), size);

}


string ctos(const char* c){
	using std::stringstream;
	stringstream sstr;
	sstr << c;
	return sstr.str();
}

string gtos(const Gauge& d, ScaleOpt opt) {
	using std::bitset;
	using std::stringstream;
	stringstream sstr;
	if (opt == ScaleOpt::bin) {
		bitset<sizeof(Gauge) * 8> num(d);
		sstr << num;
	}
	else if (opt == ScaleOpt::oct) {
		sstr << std::oct << d;
	}
	else if (opt == ScaleOpt::dec) {
		sstr << d;
	}
	else if (opt == ScaleOpt::hex) {
		sstr << std::hex << d;
	}
	return sstr.str();
}

HRESULT GetUserCode(USHORT _class, USHORT define_class, USHORT facility, USHORT result_code) {
	HRESULT hresult = 0;
	_class &= 0x3;
	hresult = (hresult | _class) << 30;
	define_class &= 0x1;
	hresult = hresult | (define_class << 29);
	facility &= 0x1FFF;
	hresult = hresult | (facility << 16);
	hresult |= result_code;
	return hresult;
}


SRE_HANDLE::SRE_HANDLE(HANDLE hProcess) {
	hd = hProcess;
	ref = new dword(0);
	(*ref)++;
}


SRE_HANDLE::SRE_HANDLE(const SRE_HANDLE& r) noexcept {
	this->hd = r.hd;
	(*r.ref) += 1;
	this->ref = r.ref;
}

SRE_HANDLE::SRE_HANDLE(SRE_HANDLE&& r) noexcept {
	this->hd = r.hd;
	r.hd = HANDLE_NULL;
	this->ref = r.ref;
	r.ref = nullptr;
}


SRE_HANDLE::operator const HANDLE() {
	return this->hd;
}


void SRE_HANDLE::operator=(HANDLE hProcess) {
	Release();
	this->hd = hProcess;
	this->ref = new dword(1);
}

bool SRE_HANDLE::operator==(HANDLE h) {
	return this->hd == h;
}
void SRE_HANDLE::Release() {
	if (this->ref !=nullptr && *this->ref != 0) {
		(*ref)--;
		if (*ref == 0 && hd != HANDLE_INVALID && hd != HANDLE_NULL) {
			delete ref;
			ref = nullptr;
			GUARD_EXCEPT(CloseHandle(hd),BadHandleRelease(GetLastError(),"An error occurred while releasing the handle."));
		}
	}

}


SRE_HANDLE::~SRE_HANDLE() {
	Release();
}
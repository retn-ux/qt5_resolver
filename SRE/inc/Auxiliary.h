#pragma once
#include <sredefs.h>
#include <vector>
#include <string>

using std::wstring;
using std::string;
using std::vector;


enum class ScaleOpt {
	bin,oct,dec,hex
};


wstring StrWStr(string ansi);
string WStrStr(wstring unicode);
void GetDataFromStr(string str, char* data, size_t size);
void GetDataFromWStr(wstring str, wchar_t* data, size_t size);
vector<string> split(string org, string sep);

HRESULT GetUserCode(USHORT _class, USHORT define_class, USHORT facility, USHORT result_code);

wstring FormatErrorMsgW(DWORD serial);
vector<string> CCharToString(char** ptr, size_t size);
/// <summary>
/// char到string的转换
/// </summary>
/// <param name="c">字符串输入</param>
/// <returns></returns>
string ctos(const char* c);

string gtos(const Gauge&d,ScaleOpt opt);
Gauge stog(const string& s);



class SRE_HANDLE {
	HANDLE hd;
	dword *ref;
public:
	SRE_HANDLE() :hd(HANDLE_NULL), ref(nullptr) {};
	SRE_HANDLE(HANDLE hProcess);
	SRE_HANDLE(const SRE_HANDLE& r) noexcept;
	SRE_HANDLE(SRE_HANDLE&& r) noexcept;
	void Release();
	operator const HANDLE();
	void operator=(HANDLE);
	bool operator==(HANDLE);
	~SRE_HANDLE();

};
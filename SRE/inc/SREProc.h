#pragma once
#include <vector>
#include <string>
using namespace std;


#include <sredefs.h>
#include <Auxiliary.h>

#define _UNOFFICIAL_DEFINE_
#include <SysDefs.h>
#include <SysExp.h>

#define MODULE_32BIT LIST_MODULES_32BIT
#define MODULE_64BIT LIST_MODULES_64BIT
#define MODULE_ALL	LIST_MODULES_ALL
#define MODULE_DEFAULT	LIST_MODULES_DEFAULT

//struct
struct PIDB {
	SRE_HANDLE hProc;
	PID pid;
};
struct PROCCORE {
	PIDB ID;
	wstring szExeFile;
};

struct MODULECORE {
	MODULEINFO mi;
	wstring theBaseName;
	wstring thePath;
};

//function
Gauge GetProcOffset(wstring module_name, string method);
void_ptr GetProcAddrEx(string dll_name, string fun_name);

Gauge GetModuleBase(HMODULE module);
bool EnumProcess(vector<PROCCORE> *pc);
vector<PROCCORE> EnumProcess();


bool GetModuleInfoOfProcess(dword flag,HANDLE hProc, vector<MODULECORE> *out);
vector<MODULECORE> GetModuleInfoOfProcess(dword flag, HANDLE hProc);
MODULECORE GetModuleInfoOfProcess(HANDLE hProc, dword flag, wstring name);
PIDB OpenProcessByName(wstring path, dword access, bool bInheritHandle = false);

//dword64 GetProcOffset64(wstring module_name, string method);
Gauge GetProcPebAddr(HANDLE hProc);
Gauge GetProcTebAddr(HANDLE hThread);
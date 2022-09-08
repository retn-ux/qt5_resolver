#ifndef _GODZILLA_PROCESS_GPROCESS_H_
#define _GODZILLA_PROCESS_GPROCESS_H_
#include <vector>
#include <string>
#include <memory>
#include <iostream>

using std::vector;
using std::wstring;

#include "config.h"

#ifdef _WINDOWS_SYSTEM_
#include <Windows.h>
#include <Psapi.h>
#pragma comment(lib,"Psapi.lib")

#include <TlHelp32.h>
#endif

#include "godzilla.h"

#include "gsystem/gsystemexp.h"

struct ProcessDesc {
	gpins_t process_ins;
	pid_t pid;
	wstring exe_file_path;
};


enum class ModuleType {
	ModuleList32Bit = 1,
	ModuleList64Bit = 2,
	ModuleListAll = (ModuleList32Bit | ModuleList64Bit)
};

struct ModuleInfo {
	void* lpBaseOfDll;	//模块基地址
	Dword SizeOfImage;	//模块大小
	void* EntryPoint;	//模块入口地址
	wstring theBaseName;
	wstring thePath;
};

enum class ProcessAccess {
#ifdef _WINDOWS_SYSTEM_
	Query=PROCESS_QUERY_INFORMATION,
	ReadMemory=PROCESS_VM_READ,
	All_Access=PROCESS_ALL_ACCESS
#endif
};


vector<pid_t> EnumProcessId();
vector<ProcessDesc> EnumProcess(ProcessAccess access);


gpins_t OpenProcess(const std::wstring& path,ProcessAccess access);
gpins_t GetProcessIns(pid_t pid, ProcessAccess access);


vector<ModuleInfo> GetProcessModules(gpins_t ins, ModuleType type);

Gauge GetPebAddress(gpins_t ins);

Gauge GetProcAddressEx(
	gpins_t ins,
	const std::wstring& module_name,
	const std::string& func_name
);

//#ifdef _WINDOWS_SYSTEM_
//vector<gpins_t> GetThreadList(gpins_t ins);
//#endif


#endif

#include "pch.h"
#include <SREProc.h>
#include <Memory.h>
#include <fstream>

Gauge GetModuleBase(HMODULE module) {
	return reinterpret_cast<Gauge>(module);
}

/*获取系统中所有进程的信息*/
bool EnumProcess(vector<PROCCORE>* pc) {
	const dword SIZE = 0x1000;
	dword ESIZE = SIZE;
	wchar_t imagePath[MAX_PATH];
	PID* pid = nullptr;
	dword lpcbNeeded = 0;
	dword i = 1;
	do {
		if (pid != nullptr)delete[] pid;
		ESIZE *= i;
		pid = new PID[ESIZE];
		i++;
		if (!EnumProcesses(pid, ESIZE, &lpcbNeeded)) {
			if (pid != nullptr)delete[] pid;
			return false;
		}
	} while (ESIZE <= lpcbNeeded / sizeof(dword));
	for (dword i = 0; i < (lpcbNeeded / sizeof(dword)); i++) {
		PROCCORE proc;
		proc.ID.pid = pid[i];
		proc.ID.hProc = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid[i]);
		if (proc.ID.hProc == nullptr || proc.ID.hProc == INVALID_HANDLE_VALUE) {
			continue;
		}
		if (GetModuleFileNameEx((HANDLE)proc.ID.hProc,nullptr, imagePath, MAX_PATH) == 0) {
			if (pid != nullptr)delete[] pid;
			return false;
		}
		proc.szExeFile = imagePath;
		pc->push_back(proc);
	}

	if (pid != nullptr)delete[] pid;
	return true;
}

vector<PROCCORE> EnumProcess() {
	vector<PROCCORE> result;
	if (!EnumProcess(&result)) {
		result.clear();
	}
	return result;
}


/*获取进程中所有模块的信息*/
bool GetModuleInfoOfProcess(dword flag, HANDLE hProc, vector<MODULECORE> *out) {
	HMODULE *module;
	dword i = 1;
	dword lpcbNeeded = 0;
	dword cb = 0;
	wchar_t path[MAX_PATH];
	wchar_t theBaseName[MAX_PATH];
	GUARD_GENTLE(EnumProcessModulesEx(hProc, nullptr, 0, &lpcbNeeded, flag), false);
	cb = lpcbNeeded;
	module = new HMODULE[cb];
	if (!EnumProcessModulesEx(hProc, module, cb, &lpcbNeeded, flag)) {
		if (module != nullptr)delete module;
		return false;
	}
	for (dword i = 0; i < cb; i++) {
		MODULECORE mi;
		if (!GetModuleInformation(hProc, module[i], &mi.mi, sizeof(mi.mi))) {
			if (module != nullptr)delete module;
			return false;
		}
		if (!GetModuleBaseName(hProc, module[i], theBaseName, sizeof(theBaseName))) {
			if (module != nullptr)delete module;
			return false;
		}
		mi.theBaseName = theBaseName;
		if (!GetModuleFileNameExW(hProc, module[i], path, sizeof(path))) {
			if (module != nullptr)delete module;
			return false;
		}
		out->push_back(mi);
	}
	
	if (module != nullptr)delete module;
	return true;
}

vector<MODULECORE> GetModuleInfoOfProcess(dword flag, HANDLE hProc) {
	vector<MODULECORE> result;
	if (!GetModuleInfoOfProcess(flag, hProc, &result)) {
		result.clear();
	}
	return result;
}


MODULECORE GetModuleInfoOfProcess(HANDLE hProc, dword flag, wstring name) {
	vector<MODULECORE> info;
	MODULECORE result;
	memset(&result, 0, sizeof(result));
	GUARD_GENTLE(GetModuleInfoOfProcess(flag, hProc,&info),result);
	GUARD_GENTLE(info.size() == 0,result);
	for (const auto &i : info) {
		if (i.theBaseName == name) {
			result = i;
			break;
		}
	}
	return result;
}


Gauge GetProcOffset(wstring module_name, string method) {
	HMODULE module = GetModuleHandle(module_name.c_str());
	Gauge module_base = GetModuleBase(module);
	if (module_base == 0) {
		return 0;
	}
	void_ptr proc_addr = ::GetProcAddress(module, method.c_str());
	Gauge relative = toGauge(proc_addr) - module_base;

	return relative;
}


void_ptr GetProcAddrEx(string dll_name, string fun_name) {
	HMODULE module = GetModuleHandleA(dll_name.c_str());
	if (module == 0) {
		module = LoadLibraryA(dll_name.c_str());
	}
	GUARD_GENTLE(module != 0, nullptr);
	return GetProcAddress(module, fun_name.c_str());
}




PIDB OpenProcessByName(wstring path, dword access, bool bInheritHandle) {
	PIDB result;
	result.hProc = HANDLE_NULL;
	result.pid = 0;
	vector<PROCCORE> info;
	GUARD_GENTLE(EnumProcess(&info), result);
	PID pid = 0;
	if (info.size() == 0) {
		return result;
	}
	wofstream os("C:\\log.txt");
	char p[MAX_PATH];
	for (const auto i : info) {
		os << i.szExeFile.c_str() << endl;
		if (i.szExeFile == path) {
			pid = i.ID.pid;

		}
	}
	HANDLE process = ::OpenProcess(access, bInheritHandle, pid);
	if (process == HANDLE_INVALID || process == HANDLE_NULL) {
		return result;
	}
	result.hProc = process;
	result.pid = pid;
	return result;
}


Gauge GetProcPebAddr(HANDLE hProc) {

	GUARD_GENTLE(hProc != INVALID_HANDLE_VALUE && hProc != nullptr, 0);
	if (hProc == GetCurrentProcess()) {
		return toGauge(NtCurrentTeb()->teb.ProcessEnvironmentBlock);
	}
	PROCESS_BASIC_INFORMATION pbi;
	memset(&pbi, 0, sizeof(PROCESS_BASIC_INFORMATION));
	ulong relen;

	NtQueryInformationProcess(hProc, ProcessBasicInformation, &pbi, sizeof(PROCESS_BASIC_INFORMATION), &relen);

	return pbi.PebBaseAddress;
}



Gauge GetProcTebAddr(HANDLE hThread) {


	
	GUARD_GENTLE(hThread != INVALID_HANDLE_VALUE && hThread != nullptr, 0);
	if (hThread == GetCurrentThread()) {
		return toGauge(NtCurrentTeb());
	}
	THREAD_BASIC_INFORMATION tbi;
	ulong relen;
	
	NtQueryInformationThread(hThread, ThreadBasicInformation, &tbi, sizeof(tbi), &relen);
	return toGauge(tbi.TebBaseAddress);

}

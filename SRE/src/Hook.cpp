#include "pch.h"
#include <Hook.h>
#include <SREProc.h>
#include <SREMemory.h>
#include <Auxiliary.h>
#include <sstream>
#include <Asm.h>


HABORIGIN ReadFunCodeToHook(string opcode, void_ptr addr, HANDLE hProcess) {
	HABORIGIN abg;
	bool IsX64 = false;
	const size_t base_read_size = 50;
#ifdef _WIN64
	IsX64 = true;
#endif
	size_t base_size = Asm("call 123", nullptr, 0, IsX64);
	byte* fun_code = new byte[base_read_size];
	abg.fun_code = fun_code;
	if (!ReadMemory(addr, fun_code, base_read_size, hProcess)) {
		delete[] fun_code;
		abg.fun_code = nullptr;
		abg.code_size = 0;
		return abg;
	}
	abg.code_size = LengthDisasm(abg.fun_code, base_read_size, base_size);
	if (abg.code_size == 0) {
		delete[] fun_code;
		abg.fun_code = nullptr;
		return abg;
	}
	byte* hook_code = new byte[abg.code_size];
	memcpy(hook_code, abg.fun_code, abg.code_size);
	delete[] fun_code;
	abg.fun_code = hook_code;
	return abg;
}






HCHIP RelaCallInstall(void_ptr tag, void_ptr hook_addr, bool idx_mode, Gauge param_offset, Gauge param_amount, HANDLE hProcess) {
	HCHIP chip;
	ZeroMemory(&chip, sizeof(chip));
	string topcode = "call 123";
	bool IsX64 = false;
	const size_t base_read_size = 50;
	size_t mem_base_size = 0x1000;
	if (hProcess == nullptr)hProcess = GetCurrentProcess();
#ifdef _WIN64
	IsX64 = true;
#endif
	size_t base_size = Asm(topcode, nullptr, 0, IsX64);
	GUARD_PTR(tag, chip);
	GUARD_PTR(hook_addr, chip);
	
	//获取被hook的代码
	chip.aborigin = ReadFunCodeToHook(topcode, hook_addr, hProcess);
	if (chip.aborigin.fun_code == nullptr) {
		return chip;
	}
	chip.hook_addr = hook_addr;
	//安装hook
	Gauge rela_addr = toGauge(chip.pedal_addr) - (toGauge(hook_addr) + base_size);
	byte* imp_code = new byte[base_size];
	stringstream ss;
	ss << "call " << hex << rela_addr;
	GUARD_GENTLE(Asm(ss.str(), imp_code, base_size, IsX64)!=0,chip);
	GUARD_GENTLE(WriteMemory(hook_addr, imp_code, base_size, hProcess), chip);
	//安装踏板代码
	byte mid_code[MACHINE_CODE_MAX_LENGTH];
	void_ptr addr_iter = chip.pedal_addr;

	size_t real_size=Asm("pushad", mid_code, MACHINE_CODE_MAX_LENGTH, IsX64);


	return chip;
}




/*


bool InjectLibrary(HANDLE process, wstring library) {
	PID pid = ::GetProcessId(process);
	GUARD_GENTLE(pid == 0, false);
	ModuleInfo remote_kernel32_info = GetModuleInfoOfProcess(pid, L"KERNEL32.DLL");
	GUARD_GENTLE(remote_kernel32_info.modBaseAddr == 0, false);
	Gauge loadlib_offset = GetProcOffset(L"kernel32.dll", "LoadLibraryW");
	void_ptr loadlibrary_addr = tovptr(remote_kernel32_info.modBaseAddr + loadlib_offset);
	if (loadlibrary_addr == nullptr)
		return false;
	void_ptr injectLib_addr_start = VirtualAllocEx(process, 0, library.size() * sizeof(wchar_t), MEM_COMMIT, PAGE_READWRITE);
	if (injectLib_addr_start == nullptr) return false;
	SIZE_T size;
	size_t libNameSize = library.size();
	void_ptr injectLib_addr = injectLib_addr_start;
	if (!WriteProcessMemory(process, injectLib_addr, library.c_str(), library.size() * sizeof(wchar_t), &size)) {
		VirtualFreeEx(process, injectLib_addr_start, 0, MEM_RELEASE);
		return false;
	}
	dword tid;
	HANDLE hThread = CreateRemoteThread(process, nullptr, 0, (LPTHREAD_START_ROUTINE)loadlibrary_addr, injectLib_addr_start, 0, &tid);
	if (hThread == HANDLE_NULL)
		VirtualFreeEx(process, injectLib_addr_start, library.size() * sizeof(wchar_t), MEM_RELEASE);
		return false;

	return true;
}




*/
#include "pch.h"
#include <SysExp.h>
#include <SREProc.h>




bool NtQueryInformationProcess(
	IN HANDLE ProcessHandle,
	IN PROCESSINFOCLASS ProcessInformationClass,
	OUT PVOID           ProcessInformation,
	IN ULONG            ProcessInformationLength,
	OUT PULONG          ReturnLength) {
	PfnNtQueryInformatioProcess fun_ptr = (PfnNtQueryInformatioProcess)GetProcAddrEx("ntdll.dll", "NtQueryInformationProcess");
	GUARD_GENTLE(fun_ptr != nullptr, false);
	if (!_NTSTATUS_SUCCESS(fun_ptr(
		ProcessHandle,
		ProcessInformationClass,
		ProcessInformation,
		ProcessInformationLength,
		ReturnLength))) {
		return false;

	}
	return true;
}

bool RtlCreateThread(
	IN HANDLE               ProcessHandle,
	IN PSECURITY_DESCRIPTOR SecurityDescriptor OPTIONAL,
	IN BOOLEAN              CreateSuspended,
	IN ULONG                StackZeroBits,
	IN OUT PULONG           StackReserved,
	IN OUT PULONG           StackCommit,
	IN PVOID                StartAddress,
	IN PVOID                StartParameter OPTIONAL,
	OUT PHANDLE             ThreadHandle,
	OUT PCLIENT_ID          ClientID) {
	PfnRtlCreateProcess fun_ptr = (PfnRtlCreateProcess)GetProcAddrEx("ntdll.dll", "RtlCreateProcess");
	GUARD_GENTLE(fun_ptr != nullptr,false);
	if (!_NTSTATUS_SUCCESS(fun_ptr(
		ProcessHandle,
		SecurityDescriptor,
		CreateSuspended,
		StackZeroBits,
		StackReserved,
		StackCommit,
		StartAddress,
		StartParameter,
		ThreadHandle,
		ClientID
	))) {
		return false;
	};
	return true;
}

bool ZwTerminateThread(HANDLE hThread, ULONG uExitCode) {
	PfnZwTerminateThread fun_ptr = (PfnZwTerminateThread)GetProcAddrEx("ntdll.dll","ZwTerminateThread");
	GUARD_GENTLE(fun_ptr != NULL, false);
	if (!_NTSTATUS_SUCCESS(fun_ptr(hThread, uExitCode))) {
		return false;
	}
	return true;
}



bool NtQueryInformationThread(
	IN HANDLE          ThreadHandle,
	IN THREADINFOCLASS ThreadInformationClass,
	OUT PVOID          ThreadInformation,
	IN ULONG           ThreadInformationLength,
	OUT PULONG         ReturnLength
) {
	PfnNtQueryInformationThread fun_ptr = (PfnNtQueryInformationThread)GetProcAddrEx("ntdll.dll","NtQueryInformationThread");
	GUARD_GENTLE(fun_ptr != NULL,false)
	if (!_NTSTATUS_SUCCESS(fun_ptr(ThreadHandle, ThreadInformationClass, ThreadInformation, ThreadInformationLength, ReturnLength))) {
		return false;
	}
	return true;

}



bool NtQuerySystemInformation(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID                   SystemInformation,
	IN ULONG                    SystemInformationLength,
	OUT PULONG                  ReturnLength
) {
	PfnNtQuerySystemInformation fun_ptr = (PfnNtQuerySystemInformation)GetProcAddrEx("ntdll.dll","NtQuerySystemInformation");
	GUARD_GENTLE(fun_ptr != nullptr, false);
	if (!_NTSTATUS_SUCCESS(fun_ptr(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength))) {
		return false;
	}
	return true;
}






/*
bool GetSystemProcessInfo(HANDLE handle) {
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	//系统应用程序最小寻址地址
	PBYTE lpAddress = (PBYTE)sysInfo.lpMinimumApplicationAddress;
	
	while(lpAddress<(PBYTE)sysInfo.lpMaximumApplicationAddress){
		MEMORY_BASIC_INFORMATION memoryInfo;
		ZeroMemory(&memoryInfo, sizeof(MEMORY_BASIC_INFORMATION));
		SIZE_T size = VirtualQueryEx(handle,lpAddress, &memoryInfo, sizeof(MEMORY_BASIC_INFORMATION));
		if (size == 0) {
			return false;
		}
		if (memoryInfo.State == MEM_COMMIT) {
			if (memoryInfo.Type == MEM_IMAGE) {
				if (GetMappedFileName(handle,) {
				
				}
			}
		}
		else if (memoryInfo.State = MEM_RESERVE) {
			lpAddress += memoryInfo.RegionSize;
			continue;
		}
		lpAddress += sysInfo.dwPageSize;
	}
}
*/




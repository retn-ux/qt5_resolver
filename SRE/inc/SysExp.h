
#include "pch.h"
#include <sredefs.h>
#include <string>
#include <SysDefs.h>
using std::string;



typedef NTSTATUS(CALLBACK* PfnNtQueryInformatioProcess)(IN HANDLE, IN PROCESSINFOCLASS, OUT PVOID, IN ULONG, OUT PULONG);
typedef NTSTATUS(WINAPI* PfnRtlCreateProcess) (IN HANDLE,IN PSECURITY_DESCRIPTOR,IN BOOLEAN,IN ULONG,IN OUT PULONG,IN OUT PULONG,IN PVOID,IN PVOID,OUT PHANDLE,OUT PCLIENT_ID);
typedef NTSTATUS(WINAPI* PfnZwTerminateThread)(HANDLE,ULONG);
typedef __kernel_entry NTSTATUS(NTAPI* PfnNtQueryInformationThread)(IN HANDLE,IN THREADINFOCLASS,OUT PVOID,IN ULONG,OUT PULONG);
typedef __kernel_entry NTSTATUS(NTAPI* PfnNtQuerySystemInformation)(IN SYSTEM_INFORMATION_CLASS ,OUT PVOID,IN ULONG,OUT PULONG);
//x86µ¼³ö		
bool NtQueryInformationProcess(
	IN HANDLE ProcessHandle,
	IN PROCESSINFOCLASS ProcessInformationClass,
	OUT PVOID           ProcessInformation,
	IN ULONG            ProcessInformationLength,
	OUT PULONG          ReturnLength);

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
	OUT PCLIENT_ID          ClientID);

bool ZwTerminateThread(HANDLE hThread, ULONG uExitCode);

bool NtQueryInformationThread(
	IN HANDLE          ThreadHandle,
	IN THREADINFOCLASS ThreadInformationClass,
	OUT PVOID          ThreadInformation,
	IN ULONG           ThreadInformationLength,
	OUT PULONG         ReturnLength
);

bool NtQuerySystemInformation(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID                   SystemInformation,
	IN ULONG                    SystemInformationLength,
	OUT PULONG                  ReturnLength
);



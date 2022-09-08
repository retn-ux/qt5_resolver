#ifndef __GOJIRA_GSYSTEMEXP_H__
#define __GOJIRA_GSYSTEMEXP_H__

#include "godzilla.h"
#include "gsystemdefs.h"

#ifdef _WINDOWS_SYSTEM_

#define NTSTATUS_SUCCESS BCRYPT_SUCCESS
#define NTDLL_LIB_NAME "ntdll.dll"

typedef NTSTATUS 
(CALLBACK* PfnNtQueryInformatioProcess)(
	IN HANDLE, 
	IN PROCESSINFOCLASS, 
	OUT PVOID, 
	IN ULONG, 
	OUT PULONG
);

typedef NTSTATUS 
(WINAPI* PfnRtlCreateProcess) (
	IN HANDLE, 
	IN PSECURITY_DESCRIPTOR, 
	IN BOOLEAN, 
	IN ULONG, 
	IN OUT PULONG, 
	IN OUT PULONG, 
	IN PVOID, 
	IN PVOID, 
	OUT PHANDLE, 
	OUT PCLIENT_ID
);

typedef NTSTATUS
(WINAPI* PfnZwTerminateThread)(
	HANDLE, 
	ULONG
);

typedef __kernel_entry NTSTATUS
(NTAPI* PfnNtQueryInformationThread)(
	IN HANDLE, 
	IN THREADINFOCLASS, 
	OUT PVOID, 
	IN ULONG, 
	OUT PULONG
);

typedef __kernel_entry NTSTATUS
(NTAPI* PfnNtQuerySystemInformation)(
	IN SYSTEM_INFORMATION_CLASS, 
	OUT PVOID, 
	IN ULONG, 
	OUT PULONG
);

typedef NTSTATUS
(NTAPI* PfnRtlAdjustPrivilege)(
	IN ULONG Privilege, 
	IN BOOLEAN Enable, 
	IN BOOLEAN CurrentThread, 
	OUT PBOOLEAN Enabled
);

typedef NTSTATUS
(NTAPI* PfnZwShutdownSystem)(
	IN SHUTDOWN_ACTION action
);

typedef void
(NTAPI* PfnNtRaiseHardError)(
	IN NTSTATUS, 
	IN ULONG, 
	IN PUNICODE_STRING, 
	IN PVOID, 
	IN HARDERROR_RESPONSE_OPTION, 
	OUT PHARDERROR_RESPONSE
);



//x86����		
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


bool RtlAdjustPrivilege
(
	ULONG    Privilege,
	BOOLEAN Enable,
	BOOLEAN CurrentThread,
	PBOOLEAN Enabled
);

bool ZwShutdownSystem(SHUTDOWN_ACTION action);


//����ֻ����false
bool NtRaiseHardError
(
	IN NTSTATUS             ErrorStatus,
	IN ULONG                NumberOfParameters,
	IN PUNICODE_STRING      UnicodeStringParameterMask OPTIONAL,
	IN PVOID* Parameters,
	IN HARDERROR_RESPONSE_OPTION ResponseOption,
	OUT PHARDERROR_RESPONSE Response
);

#endif
#endif
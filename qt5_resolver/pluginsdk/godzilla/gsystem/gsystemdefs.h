#ifndef __GOJIRA_GSYSTEMDEFS_H__
#define __GOJIRA_GSYSTEMDEFS_H__

#include "godzilla.h"
#ifdef _WINDOWS_SYSTEM_

#define STATIC_UNICODE_BUFFER_LENGTH 261
#define WIN32_CLIENT_INFO_LENGTH 0x1F
#define TEB_ACTIVE_FRAME_FLAG_EXTENDED (0x00000001)
#define GDI_BATCH_BUFFER_SIZE 310


//RtlAdjustPrivilege
#define SeCreateTokenPrivilege            0x2
#define SeAssignPrimaryTokenPrivilege     0x3
#define SeLockMemoryPrivilege             0x4
#define SeIncreaseQuotaPrivilege          0x5
#define SeUnsolicitedInputPrivilege       0x0
#define SeMachineAccountPrivilege         0x6
#define SeTcbPrivilege                    0x7
#define SeSecurityPrivilege               0x8
#define SeTakeOwnershipPrivilege          0x9
#define SeLoadDriverPrivilege             0xa
#define SeSystemProfilePrivilege          0xb
#define SeSystemtimePrivilege             0xc
#define SeProfileSingleProcessPrivilege   0xd
#define SeIncreaseBasePriorityPrivilege   0xe
#define SeCreatePagefilePrivilege         0xf
#define SeCreatePermanentPrivilege        0x10
#define SeBackupPrivilege                 0x11
#define SeRestorePrivilege                0x12
#define SeShutdownPrivilege               0x13
#define SeDebugPrivilege                  0x14
#define SeAuditPrivilege                  0x15
#define SeSystemEnvironmentPrivilege      0x16
#define SeChangeNotifyPrivilege           0x17
#define SeRemoteShutdownPrivilege         0x18
#define SeUndockPrivilege                 0x19
#define SeSyncAgentPrivilege              0x1a
#define SeEnableDelegationPrivilege       0x1b
#define SeManageVolumePrivilege           0x1c
#define SeImpersonatePrivilege            0x1d
#define SeCreateGlobalPrivilege           0x1e
#define SeTrustedCredManAccessPrivilege   0x1f
#define SeRelabelPrivilege                0x20
#define SeIncreaseWorkingSetPrivilege     0x21
#define SeTimeZonePrivilege               0x22
#define SeCreateSymbolicLinkPrivilege     0x23


//ZwShutdownSystem
typedef enum _SHUTDOWN_ACTION {
	ShutdownNoReboot,
	ShutdownReboot,
	ShutdownPowerOff
}SHUTDOWN_ACTION;


//NtRaiseHardError
typedef enum _HARDERROR_RESPONSE_OPTION {
	OptionAbortRetryIgnore,
	OptionOk,
	OptionOkCancel,
	OptionRetryCancel,
	OptionYesNo,
	OptionYesNoCancel,
	OptionShutdownSystem
} HARDERROR_RESPONSE_OPTION, * PHARDERROR_RESPONSE_OPTION;



typedef enum _HARDERROR_RESPONSE {
	ResponseReturnToCaller,
	ResponseNotHandled,
	ResponseAbort,
	ResponseCancel,
	ResponseIgnore,
	ResponseNo,
	ResponseOk,
	ResponseRetry,
	ResponseYes
} HARDERROR_RESPONSE, * PHARDERROR_RESPONSE;



typedef ULONG   PPS_POST_PROCESS_INIT_ROUTINE;

typedef LONG	KPRIORITY;

typedef enum _PROCESSINFOCLASS
{
	ProcessBasicInformation = 0, ProcessDebugPort = 7, ProcessWow64Information = 26, ProcessImageFileName = 27,
	ProcessBreakOnTermination = 29, ProcessSubsystemInformation = 75
}PROCESSINFOCLASS;





/*
typedef struct _TEB_ACTIVE_FRAME {
	ULONG Flags;
	TYPE3(struct _TEB_ACTIVE_FRAME*) Previous;
	PCTEB_ACTIVE_FRAME_CONTEXT Context;
} TEB_ACTIVE_FRAME, *PTEB_ACTIVE_FRAME;
typedef const struct _TEB_ACTIVE_FRAME *PCTEB_ACTIVE_FRAME;
*/


/*enum MSYSTEM_INFORMATION_CLASS {
	SystemBasicInformation = 0,
	SystemPerformanceInformation = 2,
	SystemTimeOfDayInformation = 3,
	SystemProcessInformation = 5,
	SystemProcessorPerformanceInformation = 8,
	SystemInterruptInformation = 23,
	SystemExceptionInformation = 33,
	SystemRegistryQuotaInformation = 37,
	SystemLookasideInformation = 45
};*/

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation,
	SystemProcessorInformation,
	SystemPerformanceInformation,
	SystemTimeOfDayInformation,
	SystemPathInformation,
	SystemProcessInformation,
	SystemCallCountInformation,
	SystemDeviceInformation,
	SystemProcessorPerformanceInformation,
	SystemFlagsInformation,
	SystemCallTimeInformation,
	SystemModuleInformation,
	SystemLocksInformation,
	SystemStackTraceInformation,
	SystemPagedPoolInformation,
	SystemNonPagedPoolInformation,
	SystemHandleInformation,
	SystemObjectInformation,
	SystemPageFileInformation,
	SystemVdmInstemulInformation,
	SystemVdmBopInformation,
	SystemFileCacheInformation,
	SystemPoolTagInformation,
	SystemInterruptInformation,
	SystemDpcBehaviorInformation,
	SystemFullMemoryInformation,
	SystemLoadGdiDriverInformation,
	SystemUnloadGdiDriverInformation,
	SystemTimeAdjustmentInformation,
	SystemSummaryMemoryInformation,
	SystemMirrorMemoryInformation,
	SystemPerformanceTraceInformation,
	SystemObsolete0,
	SystemExceptionInformation,
	SystemCrashDumpStateInformation,
	SystemKernelDebuggerInformation,
	SystemContextSwitchInformation,
	SystemRegistryQuotaInformation,
	SystemExtendServiceTableInformation,
	SystemPrioritySeperation,
	SystemVerifierAddDriverInformation,
	SystemVerifierRemoveDriverInformation,
	SystemProcessorIdleInformation,
	SystemLegacyDriverInformation,
	SystemCurrentTimeZoneInformation,
	SystemLookasideInformation,
	SystemTimeSlipNotification,
	SystemSessionCreate,
	SystemSessionDetach,
	SystemSessionInformation,
	SystemRangeStartInformation,
	SystemVerifierInformation,
	SystemVerifierThunkExtend,
	SystemSessionProcessInformation,
	SystemLoadGdiDriverInSystemSpace,
	SystemNumaProcessorMap,
	SystemPrefetcherInformation,
	SystemExtendedProcessInformation,
	SystemRecommendedSharedDataAlignment,
	SystemComPlusPackage,
	SystemNumaAvailableMemory,
	SystemProcessorPowerInformation,
	SystemEmulationBasicInformation,
	SystemEmulationProcessorInformation,
	SystemExtendedHandleInformation,
	SystemLostDelayedWriteInformation,
	SystemBigPoolInformation,
	SystemSessionPoolTagInformation,
	SystemSessionMappedViewInformation,
	SystemHotpatchInformation,
	SystemObjectSecurityMode,
	SystemWatchdogTimerHandler,
	SystemWatchdogTimerInformation,
	SystemLogicalProcessorInformation,
	SystemWow64SharedInformation,
	SystemRegisterFirmwareTableInformationHandler,
	SystemFirmwareTableInformation,
	SystemModuleInformationEx,
	SystemVerifierTriageInformation,
	SystemSuperfetchInformation,
	SystemMemoryListInformation,
	SystemFileCacheInformationEx,
	MaxSystemInfoClass  // MaxSystemInfoClass should always be the last enum
} SYSTEM_INFORMATION_CLASS;

typedef  enum  _THREADINFOCLASS
{
	ThreadBasicInformation,  //  q:  THREAD_BASIC_INFORMATION
	ThreadTimes,  //  q:  KERNEL_USER_TIMES
	ThreadPriority,  //  s:  KPRIORITY
	ThreadBasePriority,  //  s:  LONG
	ThreadAffinityMask,  //  s:  KAFFINITY
	ThreadImpersonationToken,  //  s:  HANDLE
	ThreadDescriptorTableEntry,  //  q:  DESCRIPTOR_TABLE_ENTRY  (or  WOW64_DESCRIPTOR_TABLE_ENTRY)
	ThreadEnableAlignmentFaultFixup,  //  s:  BOOLEAN
	ThreadEventPair,
	ThreadQuerySetWin32StartAddress,  //  q:  PVOID
	ThreadZeroTlsCell,  //  10
	ThreadPerformanceCount,  //  q:  LARGE_INTEGER
	ThreadAmILastThread,  //  q:  ULONG
	ThreadIdealProcessor,  //  s:  ULONG
	ThreadPriorityBoost,  //  qs:  ULONG
	ThreadSetTlsArrayAddress,
	ThreadIsIoPending,  //  q:  ULONG
	ThreadHideFromDebugger,  //  s:  void
	ThreadBreakOnTermination,  //  qs:  ULONG
	ThreadSwitchLegacyState,
	ThreadIsTerminated,  //  q:  ULONG  //  20
	ThreadLastSystemCall,  //  q:  THREAD_LAST_SYSCALL_INFORMATION
	ThreadIoPriority,  //  qs:  IO_PRIORITY_HINT
	ThreadCycleTime,  //  q:  THREAD_CYCLE_TIME_INFORMATION
	ThreadPagePriority,  //  q:  ULONG
	ThreadActualBasePriority,
	ThreadTebInformation,  //  q:  THREAD_TEB_INFORMATION  (requires  THREAD_GET_CONTEXT  +  THREAD_SET_CONTEXT)
	ThreadCSwitchMon,
	ThreadCSwitchPmu,
	ThreadWow64Context,  //  q:  WOW64_CONTEXT
	ThreadGroupInformation,  //  q:  GROUP_AFFINITY  //  30
	ThreadUmsInformation,  //  q:  THREAD_UMS_INFORMATION
	ThreadCounterProfiling,
	ThreadIdealProcessorEx,  //  q:  PROCESSOR_NUMBER
	ThreadCpuAccountingInformation,  //  since  WIN8
	ThreadSuspendCount,  //  since  WINBLUE
	ThreadHeterogeneousCpuPolicy,  //  q:  KHETERO_CPU_POLICY  //  since  THRESHOLD
	ThreadContainerId,  //  q:  GUID
	ThreadNameInformation,  //  qs:  THREAD_NAME_INFORMATION
	ThreadSelectedCpuSets,
	ThreadSystemThreadInformation,  //  q:  SYSTEM_THREAD_INFORMATION  //  40
	ThreadActualGroupAffinity,  //  since  THRESHOLD2
	ThreadDynamicCodePolicyInfo,
	ThreadExplicitCaseSensitivity,
	ThreadWorkOnBehalfTicket,
	ThreadSubsystemInformation,  //  q:  SUBSYSTEM_INFORMATION_TYPE  //  since  REDSTONE2
	ThreadDbgkWerReportActive,
	ThreadAttachContainer,
	MaxThreadInfoClass
}  THREADINFOCLASS;










template<typename T>
struct _GDI_TEB_BATCH {
	ULONG    Offset;
	T HDC;
	ULONG    Buffer[GDI_BATCH_BUFFER_SIZE];
};

typedef _GDI_TEB_BATCH<ULONG> GDI_TEB_BATCH32, * PGDI_TEB_BATCH32;
typedef _GDI_TEB_BATCH<ULONG64> GDI_TEB_BATCH64, * PGDI_TEB_BATCH64;

#ifdef _ARCH_86_
#define GDI_TEB_BATCH GDI_TEB_BATCH32
#endif
#ifdef _ARCH_64_
#define GDI_TEB_BATCH GDI_TEB_BATCH64
#endif

template<typename T>
struct _STRING {
	USHORT Length;
	USHORT MaximumLength;
	T  Buffer;
};


typedef _STRING<PVOID> STRING32, PSTRING32;
typedef _STRING<PVOID64> STRING64, PSTRING64;

template<typename T>
struct _RTL_DRIVE_LETTER_CURDIR {
	WORD Flags;
	WORD Length;
	DWORD TimeStamp;
	_STRING<T> DosPath;
};

typedef _RTL_DRIVE_LETTER_CURDIR<PVOID> RTL_DRIVE_LETTER_CURDIR32, * PRTL_DRIVE_LETTER_CURDIR32;
typedef _RTL_DRIVE_LETTER_CURDIR<PVOID64> RTL_DRIVE_LETTER_CURDIR64, * PRTL_DRIVE_LETTER_CURDIR64;


//unicode�ַ�
template<typename T>
struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	T  Buffer;
};
typedef _UNICODE_STRING<PVOID> UNICODE_STRING32, PUNICODE_STRING32;
typedef _UNICODE_STRING<PVOID64> UNICODE_STRING64, PUNICODE_STRING64;

#ifdef _ARCH_86_
#define UNICODE_STRING UNICODE_STRING32
#endif
#ifdef _ARCH_64_
#define UNICODE_STRING UNICODE_STRING64
#endif



template<typename T>
struct _CLIENT_ID {
	T UniqueProcess;
	T UniqueThread;
};
typedef _CLIENT_ID<PVOID> CLIENT_ID32, * PCLIENT_ID32;
typedef _CLIENT_ID<PVOID64>	CLIENT_ID64, * PCLIENT_ID64;

#ifdef _ARCH_86_
#define CLIENT_ID CLIENT_ID32
#endif
#ifdef _ARCH_64_
#define CLIENT_ID CLIENT_ID64
#endif


template<typename T>
struct _CURDIR {
	_UNICODE_STRING<T> DosPath;
	T Handle;
};
typedef _CURDIR<PVOID> CURDIR32, PCURDIR32;
typedef _CURDIR<PVOID64> CURDIR64, PCURDIR64;


//�ýṹ�������̲�����Ϣ�����������У�
template<typename TULONG, typename TPVOID>
struct _RTL_USER_PROCESS_PARAMETERS
{
	ULONG MaximumLength;
	ULONG Length;
	ULONG Flags;
	ULONG DebugFlags;
	TPVOID ConsoleHandle;
	ULONG ConsoleFlags;
	TPVOID StandardInput;
	TPVOID StandardOutput;
	TPVOID StandardError;
	_CURDIR<TPVOID> CurrentDirectory;
	_UNICODE_STRING<TPVOID> DllPath;
	_UNICODE_STRING<TPVOID> ImagePathName;
	_UNICODE_STRING<TPVOID> CommandLine;
	TPVOID Environment;
	ULONG StartingX;
	ULONG StartingY;
	ULONG CountX;
	ULONG CountY;
	ULONG CountCharsX;
	ULONG CountCharsY;
	ULONG FillAttribute;
	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	_UNICODE_STRING<TPVOID> WindowTitle;
	_UNICODE_STRING<TPVOID> DesktopInfo;
	_UNICODE_STRING<TPVOID> ShellInfo;
	_UNICODE_STRING<TPVOID> RuntimeData;
	_RTL_DRIVE_LETTER_CURDIR<TPVOID> CurrentDirectores[32];
	TULONG EnvironmentSize;
	TULONG EnvironmentVersion;
	TPVOID PackageDependencyData;
	ULONG ProcessGroupId;
	ULONG LoaderThreads;
	_UNICODE_STRING<TPVOID> RedirectionDllName;
};

typedef _RTL_USER_PROCESS_PARAMETERS<ULONG, PVOID> RTL_USER_PROCESS_PARAMETERS32, * PRTL_USER_PROCESS_PARAMETERS32;
typedef _RTL_USER_PROCESS_PARAMETERS<ULONG64, PVOID64> RTL_USER_PROCESS_PARAMETERS64, * PRTL_USER_PROCESS_PARAMETERS64;












typedef struct _SYSTEM_SPECULATION_CONTROL_INFORMATION {
	struct {
		ULONG BpbEnabled : 1;
		ULONG BpbDisabledSystemPolicy : 1;
		ULONG BpbDisabledNoHardwareSupport : 1;
		ULONG SpecCtrlEnumerated : 1;
		ULONG SpecCmdEnumerated : 1;
		ULONG IbrsPresent : 1;
		ULONG StibpPresent : 1;
		ULONG SmepPresent : 1;
		ULONG SpeculativeStoreBypassDisableAvailable : 1;
		ULONG SpeculativeStoreBypassDisableSupported : 1;
		ULONG SpeculativeStoreBypassDisabledSystemWide : 1;
		ULONG SpeculativeStoreBypassDisabledKernel : 1;
		ULONG SpeculativeStoreBypassDisableRequired : 1;
		ULONG BpbDisabledKernelToUser : 1;
		ULONG SpecCtrlRetpolineEnabled : 1;
		ULONG SpecCtrlImportOptimizationEnabled : 1;
		ULONG Reserved : 16;
	} SpeculationControlFlags;
} SYSTEM_SPECULATION_CONTROL_INFORMATION, * PSYSTEM_SPECULATION_CONTROL_INFORMATION;



typedef struct _SYSTEM_CODEINTEGRITY_INFORMATION {
	ULONG  Length;
	ULONG  CodeIntegrityOptions;
} SYSTEM_CODEINTEGRITY_INFORMATION, * PSYSTEM_CODEINTEGRITY_INFORMATION;

typedef struct
_SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION {
	LARGE_INTEGER IdleTime;
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER Reserved1[2];
	ULONG Reserved2;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

typedef struct _QUERY_PERFORMANCE_COUNTER_FLAGS {
	union {
		struct {
			ULONG KernelTransition : 1;
			ULONG Reserved : 31;
		};
		ULONG ul;
	};
} QUERY_PERFORMANCE_COUNTER_FLAGS;



typedef struct _SYSTEM_REGISTRY_QUOTA_INFORMATION {
	ULONG RegistryQuotaAllowed;
	ULONG RegistryQuotaUsed;
	PVOID Reserved1;
} SYSTEM_REGISTRY_QUOTA_INFORMATION;


typedef struct _SYSTEM_PROCESS_INFORMATION {
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	LARGE_INTEGER SpareLi1;
	LARGE_INTEGER SpareLi2;
	LARGE_INTEGER SpareLi3;
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING32 ImageName;
	KPRIORITY BasePriority;
	HANDLE UniqueProcessId;
	HANDLE InheritedFromUniqueProcessId;
	ULONG HandleCount;
	ULONG SessionId;
	ULONG_PTR PageDirectoryBase;
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
	SIZE_T PrivatePageCount;
	LARGE_INTEGER ReadOperationCount;
	LARGE_INTEGER WriteOperationCount;
	LARGE_INTEGER OtherOperationCount;
	LARGE_INTEGER ReadTransferCount;
	LARGE_INTEGER WriteTransferCount;
	LARGE_INTEGER OtherTransferCount;
} SYSTEM_PROCESS_INFORMATION, * PSYSTEM_PROCESS_INFORMATION;

// WinDbg> dt -v ntdll!_PEB_FREE_BLOCK
typedef struct _PEB_FREE_BLOCK // 2 elements, 0x8 bytes
{
	struct _PEB_FREE_BLOCK* pNext;
	DWORD dwSize;
} PEB_FREE_BLOCK, * PPEB_FREE_BLOCK;



template<typename TPVOID, typename TLIST_ENTRY>
struct _PEB_LDR_DATA
{
	ULONG                   Length;
	BOOLEAN                 Initialized;
	BYTE					padding[3];
	TPVOID                   SsHandle;
	TLIST_ENTRY              InLoadOrderModuleList;
	TLIST_ENTRY              InMemoryOrderModuleList;
	TLIST_ENTRY              InInitializationOrderModuleList;
	TPVOID					EntryInProgress;
	BYTE					ShutdownInProgress;
	TPVOID				ShutdownThreadId;

};

typedef _PEB_LDR_DATA<PVOID, LIST_ENTRY32> PEB_LDR_DATA32, * PPEB_LDR_DATA32;
typedef _PEB_LDR_DATA<PVOID64, LIST_ENTRY64> PEB_LDR_DATA64, * PPEB_LDR_DATA64;




//�ýṹ�����йؽ��̵��Ѽ���ģ�����Ϣ
//PEB_LDR_DATA��InMemoryOrderModuleListÿһ�ָ������ṹ
template<typename TLIST_ENTRY, typename TPVOID, DWORD Size, typename TULONG>
struct _LDR_DATA_TABLE_ENTRY
{
	TLIST_ENTRY InLoadOrderLinks;
	TLIST_ENTRY InMemoryOrderLinks;
	TLIST_ENTRY InInitializationOrderLinks;
	TPVOID DllBase;
	TPVOID EntryPoint;
	ULONG SizeOfImage;
	_UNICODE_STRING<TPVOID> FullDllName;
	_UNICODE_STRING<TPVOID> BaseDllName;
	union
	{
		BYTE FlagGroup[4];
		ULONG Flags;
	};
	USHORT LoadCount;
	USHORT TlsIndex;
	union
	{
		LIST_ENTRY HashLinks;
		struct
		{
			PVOID SectionPointer;
			ULONG CheckSum;
		};
	};
	ULONG TimeDateStamp;
	TPVOID EntryPointActivationContext;		//ָ��_ACTIVATION_CONTEXT
	TPVOID Lock;
	TPVOID DdagNode;									//ָ�� _LDR_DDAG_NODE
	TLIST_ENTRY NodeModuleLink;
	TPVOID LoadContext;							//ָ�� _LDRP_LOAD_CONTEXT
	TPVOID ParentDllBase;
	TPVOID SwitchBackContext;
	BYTE BaseAddressIndexNode[Size];			//_RTL_BALANCED_NODE
	BYTE MappingInfoIndexNode[Size];			//_RTL_BALANCED_NODE
	TULONG OriginalBase;
	LARGE_INTEGER LoadTime;
	ULONG BaseNameHashValue;
	BYTE LoadReason[0x4];							//_LDR_DLL_LOAD_REASON									
	ULONG ImplicitPathOptions;
	ULONG ReferenceCount;
	ULONG DependentLoadFlags;
	BYTE SigningLevel;
};

typedef _LDR_DATA_TABLE_ENTRY<LIST_ENTRY32, PVOID, 0xC, ULONG>	LDR_DATA_TABLE_ENTRY32, * PLDR_DATA_TABLE_ENTRY32;
typedef _LDR_DATA_TABLE_ENTRY<LIST_ENTRY64, PVOID64, 0x18, ULONG64>	LDR_DATA_TABLE_ENTRY64, * PLDR_DATA_TABLE_ENTRY64;


struct BITFIELD {
	BYTE ImageUsesLargePages : 1;
	BYTE IsProtectedProcess : 1;
	BYTE IsImageDynamicallyRelocated : 1;
	BYTE SkipPatchingUser32Forwarders : 1;
	BYTE IsPackagedProcess : 1;
	BYTE IsAppContainer : 1;
	BYTE IsProtectedProcessLight : 1;
	BYTE IsLongPathAwareProcess : 1;
};

struct TRACEFLAG {
	ULONG HeapTracingEnabled : 1;
	ULONG CritSecTracingEnabled : 1;
	ULONG LibLoaderTracingEnabled : 1;
	ULONG SpareTracingBits : 29;
};

struct LEAPSECONDFLAGS {
	ULONG SixtySecondEnabled : 1;
	ULONG Reserved : 31;

};


struct CROSSPROCESSFLAGS {
	ULONG ProcessInJob : 1;
	ULONG ProcessInitializing : 1;
	ULONG ProcessUsingVEH : 1;
	ULONG ProcessUsingVCH : 1;
	ULONG ProcessUsingFTH : 1;
	ULONG ProcessPreviouslyThrottled : 1;
	ULONG ProcessCurrentlyThrottled : 1;
	ULONG ProcessImagesHotPatched : 1;
	ULONG ReservedBits0 : 24;
};

template <typename META, DWORD size>
struct PADDING {
	META meta;
	BYTE padding[size];
};



template<typename TPVOID, typename TULONG, typename TBITFIELD, typename TCROSSPROCESSFLAGS, typename TDWORDPAD, DWORD Size, typename TLIST_ENTRY, class TTRACEFLAG>
struct _PEB // 65 elements, 0x210 bytes
{
	BYTE bInheritedAddressSpace;
	BYTE bReadImageFileExecOptions;
	BYTE bBeingDebugged;
	TBITFIELD BitField;
	TPVOID lpMutant;
	TPVOID lpImageBaseAddress;
	_PEB_LDR_DATA<TPVOID, TLIST_ENTRY>* pLdr;
	_RTL_USER_PROCESS_PARAMETERS<TULONG, TPVOID>* lpProcessParameters;
	TPVOID lpSubSystemData;
	TPVOID lpProcessHeap;
	TPVOID pFastPebLock;					//ָ��_RTL_CRITICAL_SECTION
	TPVOID AtlThunkSListPtr;				//ָ��_SLIST_HEADER		
	TPVOID IFEOKey;
	TCROSSPROCESSFLAGS CrossProcessFlags;
	union {
		TPVOID lpKernelCallbackTable;
		TPVOID UserSharedInfoPtr;
	};
	DWORD dwSystemReserved;
	DWORD dwAtlThunkSListPtr32;	//32λϵͳ��ָ��_SLIST_HEADER
	TPVOID ApiSetMap;
	TDWORDPAD dwTlsExpansionCounter;//TLS��������
	TPVOID lpTlsBitmap;//TLSλͼ
	DWORD dwTlsBitmapBits[2];//��̬Tls���̱�־λ
	TPVOID lpReadOnlySharedMemoryBase;
	TPVOID lpReadOnlySharedMemoryHeap;
	TPVOID lpReadOnlyStaticServerData;
	TPVOID lpAnsiCodePageData;
	TPVOID lpOemCodePageData;
	TPVOID lpUnicodeCaseTableData;
	DWORD dwNumberOfProcessors;
	DWORD dwNtGlobalFlag;
	LARGE_INTEGER liCriticalSectionTimeout;
	TULONG dwHeapSegmentReserve;
	TULONG dwHeapSegmentCommit;
	TULONG dwHeapDeCommitTotalFreeThreshold;
	TULONG dwHeapDeCommitFreeBlockThreshold;
	DWORD dwNumberOfHeaps;
	DWORD dwMaximumNumberOfHeaps;
	TPVOID lpProcessHeaps;
	TPVOID lpGdiSharedHandleTable;
	TPVOID lpProcessStarterHelper;
	TDWORDPAD dwGdiDCAttributeList;
	TPVOID lpLoaderLock;		//ָ�� _RTL_CRITICAL_SECTION
	DWORD dwOSMajorVersion;
	DWORD dwOSMinorVersion;
	WORD wOSBuildNumber;
	WORD wOSCSDVersion;
	DWORD dwOSPlatformId;
	DWORD dwImageSubsystem;
	DWORD dwImageSubsystemMajorVersion;
	TDWORDPAD dwImageSubsystemMinorVersion;
	DWORD ActiveProcessAffinityMask;
	DWORD dwGdiHandleBuffer[Size];
	TPVOID lpPostProcessInitRoutine;
	TPVOID lpTlsExpansionBitmap;
	DWORD dwTlsExpansionBitmapBits[32];
	TDWORDPAD dwSessionId;
	ULARGE_INTEGER liAppCompatFlags;
	ULARGE_INTEGER liAppCompatFlagsUser;
	TPVOID lppShimData;
	TPVOID lpAppCompatInfo;
	_UNICODE_STRING<TPVOID> usCSDVersion;
	TPVOID lpActivationContextData;
	TPVOID lpProcessAssemblyStorageMap;
	TPVOID lpSystemDefaultActivationContextData;
	TPVOID lpSystemAssemblyStorageMap;
	DWORD dwMinimumStackCommit;
	TPVOID FlsCallback;	//_FLS_CALLBACK_INFO
	TLIST_ENTRY FlsListHead;
	TPVOID FlsBitmap;
	DWORD FlsBitmapBits[4];
	DWORD FlsHighIndex;
	TPVOID WerRegistrationData;
	TPVOID WerShipAssertPtr;
	TPVOID pUnused;
	TPVOID pImageHeaderHash;
	TTRACEFLAG TracingFlags;
	DWORD64 CsrServerReadOnlySharedMemoryBase;
	TULONG TppWorkerpListLock;
	TLIST_ENTRY TppWorkerpList;
	TPVOID WaitOnAddressHashTable[128];
	TPVOID TelemetryCoverageHeader;
	ULONG CloudFileFlags;
	ULONG CloudFileDiagFlags;
	char PlaceholderCompatibilityMode;
	char PlaceholderCompatibilityModeReserved[0x7];
	TPVOID LeapSecondData;//_LEAP_SECOND_DATA
	ULONG LeapSecondFlags;
	DWORD NtGlobalFlag2;
};

typedef _PEB<PVOID, ULONG, BITFIELD, CROSSPROCESSFLAGS, DWORD, 34, LIST_ENTRY32, PADDING<TRACEFLAG, 4>> PEB32, * PPEB32;
typedef _PEB<PVOID64, ULONG64, PADDING<BITFIELD, 4>, PADDING<CROSSPROCESSFLAGS, 4>, PADDING<DWORD, 4>, 60, LIST_ENTRY64, PADDING<TRACEFLAG, 4>> PEB64, * PPEB64;



template<class TDWORD>
struct _PROCESS_BASIC_INFORMATION
{

	TDWORD ExitStatus; // ���ս�����ֹ״̬

	TDWORD PebBaseAddress; // ���ս��̻������ַ

	TDWORD AffinityMask; // ���ս��̹�������

	TDWORD BasePriority; // ���ս��̵����ȼ���

	TDWORD UniqueProcessId; // ���ս���ID

	TDWORD InheritedFromUniqueProcessId; //���ո�����ID

};

typedef _PROCESS_BASIC_INFORMATION<DWORD> PROCESS_BASIC_INFORMATION32, * PPROCESS_BASIC_INFORMATION32;
typedef _PROCESS_BASIC_INFORMATION<DWORD64> PROCESS_BASIC_INFORMATION64, * PPROCESS_BASIC_INFORMATION64;

//����ṹ�����и����̵�ID����Ӧ�Ĺٷ��� Reserved3�ֶΣ�
//���н��̵�PEB����һ�½��̻�������Ķ��壺*/


typedef struct _THREAD_BASIC_INFORMATION32
{
	NTSTATUS                ExitStatus;
	PVOID                  TebBaseAddress;
	CLIENT_ID               ClientId;
	KAFFINITY               AffinityMask;
	KPRIORITY               Priority;
	KPRIORITY               BasePriority;
} THREAD_BASIC_INFORMATION32, * PTHREAD_BASIC_INFORMATION32;

typedef struct _THREAD_BASIC_INFORMATION64
{
	NTSTATUS                ExitStatus;
	DWORD					Padding;
	PVOID                  TebBaseAddress;
	CLIENT_ID               ClientId;
	KAFFINITY               AffinityMask;
	KPRIORITY               Priority;
	KPRIORITY               BasePriority;
} THREAD_BASIC_INFORMATION64, * PTHREAD_BASIC_INFORMATION64;


#ifdef _WRK_
typedef struct _SYSTEM_PROCESS_INFORMATION {
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	LARGE_INTEGER SpareLi1;
	LARGE_INTEGER SpareLi2;
	LARGE_INTEGER SpareLi3;
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ImageName;
	KPRIORITY BasePriority;
	HANDLE UniqueProcessId;
	HANDLE InheritedFromUniqueProcessId;
	ULONG HandleCount;
	ULONG SessionId;
	ULONG_PTR PageDirectoryBase;
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
	SIZE_T PrivatePageCount;
	LARGE_INTEGER ReadOperationCount;
	LARGE_INTEGER WriteOperationCount;
	LARGE_INTEGER OtherOperationCount;
	LARGE_INTEGER ReadTransferCount;
	LARGE_INTEGER WriteTransferCount;
	LARGE_INTEGER OtherTransferCount;
} SYSTEM_PROCESS_INFORMATION, * PSYSTEM_PROCESS_INFORMATION;

#endif







/*
//�ж�����������
typedef struct _KIDTENTRY {
	USHORT Offset;
	USHORT Selector;
	USHORT Access;
	USHORT ExtendedOffset;
}KIDTENTRY;
typedef KIDTENTRY *PKIDTENTRY;


//SYSTEM SERVER DESCRIPTOR TABLE(KeServiceDescriptorTable)
typedef struct _KSERVER_TABLE_DESCRIPTOR {
	PULONG Base;	//����ַ ָ��KeServiceTable
	PULONG Count;
	ULONG Limit;	//�ܸ���
	PUCHAR Number; //����������
}KSERVER_TABLE_DESCRIPTOR, *PKSERVER_TABLE_DESCRIPTOR;


//SYSTEM SERVER DESCRIPTOR SHADOW(KeServiceDescriptorTableShadow)
typedef struct _KSERVER_TABLE_DESCRIPTOR_SHADOW{
	//������KeServiceDescriptorTable��ȫһ��
	PULONG Base;	//����ַ ָ��KeServiceTable
	PULONG Count;
	ULONG Limit;	//�ܸ���
	PUCHAR Number; //����������
	//����ʱShadow�Ķ��б���
	PULONG BaseOfShadow;	//����ַ ָ��W32pServiceTable
	PULONG CountOfShadow;
	ULONG LimitOfShadow;	//�ܸ���
	PUCHAR NumberOfShadow; //����������
}KSERVER_TABLE_DESCRIPTOR_SHADOW, *PKSERVER_TABLE_DESCRIPTOR_SHADOW;






typedef NTSYSCALLAPI NTSTATUS (NTAPI *PNTQUERYINFOMATIONTHREAD)(
	_In_  HANDLE  ,
	_In_  THREADINFOCLASS  ,
	_Out_  PVOID  ,
	_In_  ULONG  ,
	_Out_opt_  PULONG
);
*/
/*typedef struct _CLIENTINFO {
	DWORD               CI_flags;               // Needs to be first because CSR
	DWORD               cSpins;
	DWORD               dwExpWinVer;
	DWORD               dwCompatFlags;
	DWORD               dwTIFlags;
	PDESKTOPINFO        pDeskInfo;
	ULONG               ulClientDelta;
	struct tagHOOK      *phkCurrent;
	DWORD               fsHooks;
	CALLBACKWND         CallbackWnd;
	DWORD               dwHookCurrent;
	int                 cInDDEMLCallback;
	HANDLE              hDdemlCallbackInst;
	PCLIENTTHREADINFO   pClientThreadInfo;
	DWORD               dwHookData;
	DWORD               dwKeyCache;
	BYTE                afKeyState[CBKEYCACHE];
	DWORD               dwAsyncKeyCache;
	BYTE                afAsyncKeyState[CBASYNCKEYCACHE];
	BYTE                afAsyncKeyStateRecentDown[CBASYNCKEYCACHE];
	WORD                CodePage;
	HKL                 hKL;

	BYTE                achDbcsCF[2]; // Save ANSI DBCS LeadByte character code
									  // in this field for ANSI to Unicode.
									  // Uses SendMessageA/PostMessageA from CLIENT
									  // to SERVER (index 0)
									  //  And...
									  // Uses SendMessageA/DispatchMessageA
									  // for CLIENT to CLIENT (index 1)
	MSG                 msgDbcsCB;    // Save ANSI DBCS character message in
									  // this field for convert Unicode to ANSI.
									  // Uses GetMessageA/PeekMessageA from
									  // SERVER to CLIENT
} CLIENTINFO, *PCLIENTINFO;*/
/*typedef struct _KPCR
{
	_ANONYMOUS_UNION union
	{
		NT_TIB NtTib;//�����ǵ�ǰ�̵߳Ŀ��ƿ�
		_ANONYMOUS_STRUCT struct
		{
			union _KGDTENTRY64 *GdtBase;///gdt��
			struct _KTSS64 *TssBase;
			ULONG64 UserRsp;
			struct _KPCR *Self;
			struct _KPRCB *CurrentPrcb;
			PKSPIN_LOCK_QUEUE LockArray;
			PVOID Used_Self;
		};
	};
	union _KIDTENTRY64 *IdtBase;
	ULONG64 Unused[2];
	KIRQL Irql;
	UCHAR SecondLevelCacheAssociativity;
	UCHAR ObsoleteNumber;
	UCHAR Fill0;
	ULONG Unused0[3];
	USHORT MajorVersion;
	USHORT MinorVersion;
	ULONG StallScaleFactor;
	PVOID Unused1[3];
	ULONG KernelReserved[15];
	ULONG SecondLevelCacheSize;
	ULONG HalReserved[16];
	ULONG Unused2;
	PVOID KdVersionBlock;
	PVOID Unused3;
	ULONG PcrAlign1[24];
} KPCR, *PKPCR;*/

typedef struct _ACTIVATION_CONTEXT_STACK {
	PVOID ActiveFrame;	//_RTL_ACTIVATION_CONTEXT_STACK_FRAME
	LIST_ENTRY FrameListCache;
	DWORD Flags;
	DWORD NextCookieSequenceNumber;
	DWORD StackId;
}ACTIVATION_CONTEXT_STACK, * PACTIVATION_CONTEXT_STACK;

typedef struct _TXFSCONTEXTBLOCK32 {
	UCHAR InstrumentationCallbackDisabled;
	UCHAR SpareBytes[23];
	DWORD TxFsContext;
}TXFSCONTEXTBLOCK32;

typedef struct _TXFSCONTEXTBLOCK64 {
	DWORD TxFsContext;
	BYTE InstrumentationCallbackDisabled;
	BYTE UnalignedLoadStoreExceptions;
	BYTE Padding[2];
}TXFSCONTEXTBLOCK64;

struct PADSTATICNICODEBUFFER32 {
	BYTE StaticUnicodeBuffer[261];
};

struct PADSTATICNICODEBUFFER64 {
	BYTE StaticUnicodeBuffer[261];
	BYTE padding[6];
};

/*************************************************************
*TEB
***********************************************************/
template<DWORD SystemReserved1Size, class TPADINT, class TDWORD, class TXFSCONTEXTBLOCK, class TPADDWORD, class TPADStaticUnicodeBuffer, DWORD InstrumentationSize>
struct __TEB {
	NT_TIB NtTib;
	PVOID EnvironmentPointer;
	CLIENT_ID ClientId;
	PVOID ActiveRpcHandle;
	PVOID ThreadLocalStoragePointer;// //ָ���ž�̬TLS���ݵĵ�ַ��ָ��ĵ�ַ
	PVOID ProcessEnvironmentBlock;
	ULONG LastErrorValue;
	ULONG CountOfOwnedCriticalSections;
	PVOID CsrClientThread;
	PVOID Win32ThreadInfo;// PtiCurrent
	DWORD User32Reserved[26];// User32 Client Info
	DWORD UserReserved[5];
	PVOID WOW32Reserved;// used by WOW
	LCID CurrentLocale;
	ULONG FpSoftwareStatusRegister;
	PVOID ReservedForDebuggerInstrumentation[16];// Used by FP emulator
	PVOID SystemReserved1[SystemReserved1Size];
	CHAR PlaceholderCompatibilityMode;
	BYTE PlaceholderHydrationAlwaysExplicit;
	CHAR PlaceholderReserved[10];
	DWORD ProxiedProcessId;
	ACTIVATION_CONTEXT_STACK _ActivationStack;
	BYTE WorkingOnBehalfTicket[0x8];
	TPADINT ExceptionCode;
	PVOID ActivationContextStackPointer;// _ACTIVATION_CONTEXT_STACK
	TDWORD InstrumentationCallbackSp;
	TDWORD InstrumentationCallbackPreviousPc;
	TDWORD InstrumentationCallbackPreviousSp;
	TXFSCONTEXTBLOCK TxFsContext;
	GDI_TEB_BATCH GdiTebBatch;// Gdi batching
	CLIENT_ID RealClientId;
	PVOID GdiCachedProcessHandle;
	DWORD GdiClientPID;
	DWORD GdiClientTID;
	PVOID GdiThreadLocalInfo;
	TDWORD Win32ClientInfo[62];
	PVOID glDispatchTable[233];
	TDWORD glReserved1[29];
	PVOID glReserved2;
	PVOID glSectionInfo;
	PVOID glSection;
	PVOID glTable;
	PVOID glCurrentRC;
	PVOID glContext;
	TPADDWORD PadLastStatusValue;
	UNICODE_STRING StaticUnicodeString;
	TPADStaticUnicodeBuffer PadStaticUnicodeBuffer;
	PVOID DeallocationStack;
	PVOID TlsSlots[TLS_MINIMUM_AVAILABLE];  //ָ���Ŷ�̬TLS���ݵ�TLS Slot����
	LIST_ENTRY TlsLinks;
	PVOID Vdm;
	PVOID ReservedForNtRpc;
	PVOID DbgSsReserved[2];
	TPADDWORD PadHardErrorsAreDisabled;
	PVOID Instrumentation[InstrumentationSize];
	GUID ActivityId;
	PVOID SubProcessTag;
	PVOID PerflibData;
	PVOID EtwTraceData;
	PVOID WinSockData;// WinSock
	ULONG GdiBatchCount;
	union {
		PROCESSOR_NUMBER CurrentIdealProcessor;
		DWORD IdealProcessorValue;
		struct {
			BYTE ReservedPad0;
			BYTE ReservedPad1;
			BYTE ReservedPad2;
			BYTE IdealProcessor;
		};
	};
	TPADDWORD PadGuaranteedStackBytes;
	PVOID ReservedForPerf;
	PVOID ReservedForOle;
	TPADDWORD PadWaitingOnLoaderLock;
	PVOID SavedPriorityState;
	TDWORD ReservedForCodeCoverage;
	PVOID ThreadPoolData;
	PVOID TlsExpansionSlots;
	PVOID DeallocationBStore;
	PVOID BStoreLimit;
	DWORD MuiGeneration;
	DWORD IsImpersonating;
	PVOID NlsCache;
	PVOID pShimData;
	TPADDWORD PadHeapData;
	PVOID CurrentTransactionHandle;
	PVOID ActiveFrame;// _TEB_ACTIVE_FRAME
	PVOID FlsData;
	PVOID PreferredLanguages;
	PVOID UserPrefLanguages;
	PVOID MergedPrefLanguages;
	DWORD MuiImpersonation;
	union {
		WORD CrossTebFlags;
		WORD SpareCrossTebBits;
	};
	union {
		WORD SameTebFlags;
		struct {
			WORD SafeThunkCall : 1;
			WORD InDebugPrint : 1;
			WORD HasFiberData : 1;
			WORD SkipThreadAttach : 1;
			WORD WerInShipAssertCode : 1;
			WORD RanProcessInit : 1;
			WORD ClonedThread : 1;
			WORD SuppressDebugMsg : 1;
			WORD DisableUserStackWalk : 1;
			WORD RtlExceptionAttached : 1;
			WORD InitialThread : 1;
			WORD SessionAware : 1;
			WORD LoadOwner : 1;
			WORD LoaderWorker : 1;
			WORD SkipLoaderInit : 1;
			WORD SpareSameTebBits : 1;
		};

	};
	PVOID TxnScopeEnterCallback;
	PVOID TxnScopeExitCallback;
	PVOID TxnScopeContext;
	DWORD LockCount;
	int WowTebOffset;
	PVOID ResourceRetValue;
	PVOID ReservedForWdf;
	TDWORD ReservedForCrt;
	GUID EffectiveContainerId;

};

typedef __TEB<26, int, DWORD, TXFSCONTEXTBLOCK32, DWORD, PADSTATICNICODEBUFFER32, 11> TEB32, * PTEB32;
typedef __TEB<30, PADDING<int, 4>, DWORD64, TXFSCONTEXTBLOCK64, PADDING<DWORD, 4>, PADSTATICNICODEBUFFER64, 9> TEB64, * PTEB64;

#ifdef _ARCH_86_

#define TEB TEB32
#define PTEB PTEB32
#define PEB PEB32
#define PPEB PPEB32
#define PROCESS_BASIC_INFORMATION PROCESS_BASIC_INFORMATION32
#define CLIENT_ID CLIENT_ID32
#define PCLIENT_ID PCLIENT_ID32
#define THREAD_BASIC_INFORMATION THREAD_BASIC_INFORMATION32
#define UNICODE_STRING UNICODE_STRING32 
#endif

#ifdef _ARCH_64_
#define PEB PEB64
#define PPEB PPEB64
#define PROCESS_BASIC_INFORMATION PROCESS_BASIC_INFORMATION64
#define TEB TEB64
#define PTEB PTEB64;
#define CLIENT_ID CLIENT_ID64
#define PCLIENT_ID PCLIENT_ID64
#define THREAD_BASIC_INFORMATION THREAD_BASIC_INFORMATION64
#define UNICODE_STRING UNICODE_STRING64
#endif

typedef UNICODE_STRING* PUNICODE_STRING;

struct _TEB {
	TEB teb;
};
#endif
#endif
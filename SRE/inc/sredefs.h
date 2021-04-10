#include <cassert>
#include <SRE.h>





#define HANDLE_NULL nullptr
#define HANDLE_INVALID INVALID_HANDLE_VALUE
#define HMODULE_NULL 0

#define _NTSTATUS_SUCCESS BCRYPT_SUCCESS



#define GUARD_SEVERE assert
#define GUARD_GENTLE(pred,ret) if(!(pred))return ret;
#define GUARD_EXCEPT(predi,except) if(!(predi))throw except;

#define GUARD_HANDLE(handle,revalue) GUARD_GENTLE(handle!=nullptr,revalue)
#define GUARD_ADDR(addr,ret) GUARD_GENTLE(addr!=0,ret)
#define GUARD_PTR(ptr,ret)	GUARD_GENTLE(ptr!=nullptr,ret)

typedef DWORD dword;
typedef WORD word;
typedef BYTE byte; 
typedef USHORT ushort;


typedef LPVOID void_ptr;
typedef PVOID64 fvoid_ptr;

typedef ULONG64 ulong64;

typedef ULONG ulong;

typedef dword PID;

typedef DWORD64 fword;

#ifndef _WIN64
typedef DWORD Gauge;
#else
typedef DWORD64 Gauge;
#endif





#define tovptr(d)\
	reinterpret_cast<void_ptr>(d)

#define toGauge(v)\
	reinterpret_cast<Gauge>(v)

#define todword(v)\
	reinterpret_cast<dword>(v)

#define tofword(v)\
	reinterpret_cast<fword>(v)

#define todword64(v) tofword(v)




#ifdef __HRESULT_INFO__
#define HRESULT_CLASS_SUCCESS 0
#define HRESULT_CLASS_CONTAINS_INFORMATION 1
#define HRESULT_CLASS_WARNNING 2
#define HRESULT_CLASS_ERROR 3
//从HRESULT中获取类别
#define GetClassFormValue(hresult,_class)\
	_class=hresult&0xC0000000;\
	_class >>= 30;

#define HRESULT_USER_DEFINE 1
#define HRESULT_NOT_USER_DEFINE 0
#define GetDefineClassFromValue(hresult,_class)\
	_class=hresult&0x20000000;\
	_class >>= 29;


#define GetFacilityFromValue(hresult,_class)\
	_class=hresult&0x1FFF0000;\
	_class>>=16;


#define GetResultCodeFromValue(hresult,_class)\
	_class=hresult&0xFFFF;


#endif // __WIN__


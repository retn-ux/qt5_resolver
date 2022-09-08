#ifndef _GODZILLA_GODZILLA_H_
#define _GODZILLA_GODZILLA_H_

#include "config.h"

#ifdef _WINDOWS_SYSTEM_
#include <Windows.h>




typedef DWORD pid_t;

typedef HANDLE gpins_t;

#define GPINS_INVALID(ins)\
	(ins == INVALID_HANDLE_VALUE || ins == nullptr)


#define INVALID_GPINS_T nullptr

typedef DWORD64 Fword;
typedef DWORD Dword;
typedef WORD Word;
typedef BYTE Byte;

#endif

#ifdef _LINUX_SYSTEM_
#include <sys/types.h>

typedef uint64_t Fword;
typedef uint32_t Dword;
typedef uint16_t Word;
typedef uint8_t Byte;

typedef pid_t gpins_t;

#define GPINS_INVALID(ins)\
	(ins == 0)

#define INVALID_GPINS_T 0

#endif


typedef unsigned long ulong;

#ifdef _ARCH_86_
typedef Dword Gauge;
#endif


#ifdef _ARCH_64_
typedef Fword Gauge;
#endif


#define GAUGE_CAST(value)\
	reinterpret_cast<Gauge>(value)


#define VOID_PTR_CAST(value)\
	reinterpret_cast<void*>(value)

#endif
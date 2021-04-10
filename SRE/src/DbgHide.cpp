#include "pch.h"
#include <DbgHide.h>
#include <Process.h>
#include <Memory.h>
/*
bool HideProcPebFlags(HANDLE hProc) {


	dword peb_addr = GetProcPebAddr(hProc);
	PEB peb;
	GUARD_GENTLE(ReadMemory(tovptr(peb_addr), &peb, sizeof(PEB),hProc),false);

	peb.bBeingDebugged = 0;
	peb.dwNtGlobalFlag &= (~0x70);

	GUARD_GENTLE(ReadMemory(tovptr(peb_addr), &peb, sizeof(PEB), hProc), false);

	

	
	GUARD_GENTLE(WriteMemory(tovptr(peb_addr), &peb, sizeof(PEB), hProc), false);

	return true;
}*/
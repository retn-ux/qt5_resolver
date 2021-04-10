#pragma once
#include <sredefs.h>
#include <SysExp.h>
#include <string>
using std::string;

word ReversalWord(word value);
dword ReversalDword(dword value);
fword ReversalFword(fword value);

#ifndef _WIN64
#define ReversalGauge ReversalDword
#else
#define ReversalGauge ReversalFword
#endif

bool ReadMemory(void_ptr tag, void_ptr buff, size_t size, HANDLE hProcess = nullptr);

bool WriteMemory(void_ptr tag, void_ptr buff, size_t size, HANDLE hProcess = nullptr);



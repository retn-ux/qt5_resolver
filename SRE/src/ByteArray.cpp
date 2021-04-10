#include "pch.h"
#include "ByteArray.h"


ulong bytelen(const byte* src) {
	ulong i = 0;
	for (; src[i] != '\0'; i++);
	return i+1;
}

int bytecmp(const byte* p, const byte* d) {
	return strcmp(reinterpret_cast<const char *>(p), reinterpret_cast<const char*>(d));
}


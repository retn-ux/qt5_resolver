#include "pch.h"

#include <SREMemory.h>

#define ReadMemoryBySize(start,size,buffer)\
	for(int i=start;i<start+size;i++){\
		buffer[i]=start[i];\
	}




bool ReadMemory(void_ptr src, void_ptr buff, size_t size, HANDLE hProcess) {
	GUARD_GENTLE(src != nullptr, false);
	GUARD_GENTLE(buff != nullptr, false);
	if (hProcess == nullptr) {
		memcpy(buff, src, size);
	}
	else {
		GUARD_HANDLE(hProcess, false);
		SIZE_T nums = 0;
		GUARD_GENTLE(ReadProcessMemory(hProcess, src, buff, size, &nums), false);
		GUARD_GENTLE(nums == size, false);
	}
	return true;
}

bool WriteMemory(void_ptr src,void_ptr buff, size_t size, HANDLE hProcess) {
	GUARD_GENTLE(src != nullptr, false);
	GUARD_GENTLE(buff != nullptr, false);
	if (hProcess == nullptr) {
		memcpy(src, buff, size);
	}
	else {
		GUARD_HANDLE(hProcess, false);
		SIZE_T nums = 0;
		GUARD_GENTLE(WriteProcessMemory(hProcess, src, buff, size, &nums), false);
		GUARD_GENTLE(nums == size, false);
	}
	return true;
}


dword ReversalDword(dword value) {
	word low = (value & 0xFFFF);
	word high = (value & 0xFFFFF0000) >> 16;
	word ret_high=ReversalWord(low);
	word ret_low = ReversalWord(high);
	dword ret = ((ret_high << 16) | ret_low);
	return ret;
}



word ReversalWord(word value) {
	word little = ((value & 0xFF00) >> 8);
	little |= ((value & 0xFF) << 8);
	return little;
}

fword ReversalFword(fword value) {
	fword magic_high = 0xFFFFFFFF00000000;
	fword low = (value & 0xFFFFFFFF);
	fword high = (value & magic_high)>>32;
	fword ret_high = ReversalDword(low);
	fword ret_low = ReversalDword(high);
	fword ret = ret_high << 32;
	ret |= ret_low;
	return ret;
}

#include "pch.h"
#include <CorAux.h>

/*
IImgMdtTable* CreateMethodTable() {
	using dynamic::Image::ImgMdtMethodTableEx;
	return new ImgMdtMethodTableEx();
}


inline ICMethodHdrType GetMethodHeaderType(ImgMdtMethodHdr *mdtMethodHeader) {
	if (mdtMethodHeader == nullptr) {
		return ICMethodHdrType::other;
	}
	WORD* wr = (WORD*)mdtMethodHeader;
	if (*wr == 0x2) {
		return ICMethodHdrType::tiny;
	}
	else {
		return ICMethodHdrType::fat;
	}
	return ICMethodHdrType::other;
}*/
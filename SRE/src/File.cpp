#include "pch.h"
#include <file.h>


LPVOID CreateImageMapFile(IN string fileName, IN DWORD maxSize, OUT IMAGE_MAP_INFO* info, OUT DWORD *result) {
	ZeroMemory(info, sizeof(IMAGE_MAP_INFO));
	HANDLE fileHandle = nullptr;
	LPVOID address = 0;
	*result = 0;
	if (fileName.empty()) {
		*result = 0xFFFFFFFF;
		return address;
	}

	fileHandle = ::CreateFileA(fileName.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (fileHandle == INVALID_HANDLE_VALUE || fileHandle == 0) {
		*result = GetLastError();
		return address;
	}
	HANDLE mapHandle;
	mapHandle = ::CreateFileMappingA(fileHandle, nullptr, PAGE_READWRITE, 0, maxSize, nullptr);
	if (mapHandle == INVALID_HANDLE_VALUE || mapHandle == 0) {
		CloseHandle(fileHandle);
		*result = GetLastError();
		return address;
	}
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	address = (DWORD*)::MapViewOfFile(mapHandle, FILE_MAP_ALL_ACCESS, 0, 0, maxSize);
	if (address == 0) {
		CloseHandle(mapHandle);
		CloseHandle(fileHandle);
		*result = GetLastError();
		return address;
	}
	info->file = fileHandle;
	info->map = mapHandle;
	return address;
}


LPVOID CreateImageMapFile(IN HANDLE file,
						IN DWORD maxSize,
						IN DWORD flMappingProtect,
						IN DWORD flMappingDesiredAccess,
						OUT HANDLE &map, OUT DWORD* result) 
{
	map = nullptr;
	LPVOID address = 0;
	*result = 0;
	if (file == INVALID_HANDLE_VALUE || file == 0) {
		*result = 0xFFFFFFFF;
		return address;
	}
	HANDLE mapHandle;
	mapHandle = ::CreateFileMappingA(file, nullptr, flMappingProtect, 0, maxSize, nullptr);
	if (mapHandle == INVALID_HANDLE_VALUE || mapHandle == 0) {
		*result = GetLastError();
		return address;
	}
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	address = (DWORD*)::MapViewOfFile(mapHandle, flMappingDesiredAccess, 0, 0, maxSize);
	if (address == 0) {
		CloseHandle(mapHandle);

		*result = GetLastError();
		return address;
	}

	map = mapHandle;
	return address;
}

bool UnmapOfFile(IN LPVOID addr, IMAGE_MAP_INFO* info) {
	if (info->map != nullptr&&!CloseHandle(info->map)) {
		return false;
	}
	if (UnmapViewOfFile(addr)) {
		return false;
	}
	if (info->file != nullptr && !CloseHandle(info->file)) {
		return false;
	}
	return true;
}

bool UnmapOfFile(IN LPVOID addr, HANDLE map) {
	if (map == nullptr||map==INVALID_HANDLE_VALUE && !CloseHandle(map)) {
		return false;
	}
	if (!UnmapViewOfFile(addr)) {
		return false;
	}

	return true;
}




DWORD SetFileSize(string fileName, LONG size,DWORD mode) {
	HANDLE file = ::CreateFileA(fileName.c_str(),GENERIC_READ, FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	LARGE_INTEGER large;
	if (file == INVALID_HANDLE_VALUE || file == 0) {
		return GetLastError();
	}
	if (!GetFileSizeEx(file, &large)) {
		CloseHandle(file);
		return GetLastError();
	}
	if (mode == FILE_SIZE_ADD) {
		large.QuadPart += size;
	}
	else if (mode == FILE_SIZE_SUB) {
		if (large.QuadPart < size) {
			CloseHandle(file);
			return 0xFFFFFFFF;
		}
		large.QuadPart -= size;
	}
	
	DWORD result=::SetFilePointerEx(file, large, NULL, FILE_BEGIN);

	if (result == 0xFFFFFFFF && GetLastError() != NO_ERROR) {
		CloseHandle(file);
		return GetLastError();
	}
	if (!SetEndOfFile(file)) {
		CloseHandle(file);
		return GetLastError();
	}
	CloseHandle(file);
	return 0;
}


DWORD SetFileSize(HANDLE file, LONG size, DWORD mode) {
	LARGE_INTEGER large;
	if (file == INVALID_HANDLE_VALUE || file == 0) {
		return GetLastError();
	}
	if (!GetFileSizeEx(file, &large)) {
		CloseHandle(file);
		return GetLastError();
	}
	if (mode == FILE_SIZE_ADD) {
		large.QuadPart += size;
	}
	else if (mode == FILE_SIZE_SUB) {
		if (large.QuadPart < size) {
			CloseHandle(file);
			return 0xFFFFFFFF;
		}
		large.QuadPart -= size;
	}

	DWORD result = ::SetFilePointerEx(file, large, NULL, FILE_BEGIN);

	if (result == 0xFFFFFFFF && GetLastError() != NO_ERROR) {
		CloseHandle(file);
		return GetLastError();
	}
	if (!SetEndOfFile(file)) {
		CloseHandle(file);
		return GetLastError();
	}
	CloseHandle(file);
	return 0;
}



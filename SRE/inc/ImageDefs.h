#pragma once
#include <sredefs.h>
#define ADDR_ERROR 1
#define NOT_FOUND_MDT_TABLE_STREAM	0x8
#define SIZE_TO_LOW	0x10
#define MODE_ERROR 0x20
#define NAME_TO_LONG 0x40
#define HANDLE_ERROR 0x80
#define READ_ERROR 0x100
#define WRITE_ERROR 0x200
#define INDEX_ERROR 0x400
#define NAME_ERROR 0x800
#define UNINIT 0x1000


#define IMAGE_EXCEPTION_HANDING_TABLE IMAGE_LOAD_CONFIG_DIRECTORY
#define PIMAGE_EXCEPTION_HANDING_TABLE PIMAGE_LOAD_CONFIG_DIRECTORY




typedef enum class IMAGE_MODE {
	File,Memory
} ImageMode;

#define GetNext(base,obj)\
	base = LPVOID((DWORD)base + obj.GetSize());


#define GetNextTable(base,obj)\
	base = LPVOID((DWORD)base + obj->GetTableSize());
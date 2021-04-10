#pragma once
/*
#include <Windows.h>
#include <CorTableMgr.h>
using dynamic::Image::IImgMdtTable;
using dynamic::Image::ImgMdtMethodHdr;

struct ImgMdtStmMask {
	static const ULONGLONG Module = 0x1; static const ULONGLONG TypeRef = 0x2; static const ULONGLONG TypeDef = 0x4;
	static const ULONGLONG FieldPtr = 0x8; static const ULONGLONG Field = 0x10; static const ULONGLONG MethodPtr = 0x20;
	static const ULONGLONG Method = 0x40; static const ULONGLONG ParamPtr = 0x80; static const ULONGLONG Param = 0x100;
	static const ULONGLONG InterfaceImpl = 0x200; static const ULONGLONG MemberRef = 0x400; static const ULONGLONG Constant = 0x800;
	static const ULONGLONG CustomAttribute = 0x1000; static const ULONGLONG FieldMarshal = 0x2000; static const ULONGLONG DeclSecurity = 0x4000;
	static const ULONGLONG ClassLayout = 0x8000; static const ULONGLONG FieldLayout = 0x10000; static const ULONGLONG StandAloneSig = 0x20000;
	static const ULONGLONG EventMap = 0x40000; static const ULONGLONG EventPtr = 0x80000; static const ULONGLONG Event=0x100000;
	static const ULONGLONG PropertyMap = 0x200000; static const ULONGLONG PropertyPtr = 0x400000; static const ULONGLONG Property = 0x800000;
	static const ULONGLONG MethodSemantics = 0x1000000; static const ULONGLONG MethodImpl = 0x2000000; static const ULONGLONG ModuleRef = 0x4000000;
	static const ULONGLONG TypeSpec = 0x8000000; static const ULONGLONG ImplMap = 0x10000000; static const ULONGLONG FieldRVA = 0x20000000;
	static const ULONGLONG ENCLog = 0x40000000; static const ULONGLONG ENCMap = 0x80000000; static const ULONGLONG Assembly = 0x100000000;
	static const ULONGLONG AssemblyProcessor = 0x200000000; static const ULONGLONG AssemblyOS = 0x4000000000; 
	static const ULONGLONG AssemblyRef = 0x800000000;static const ULONGLONG AssemblyRefProcessor = 0x1000000000; 
	static const ULONGLONG AssemblyRefOS = 0x2000000000; static const ULONGLONG File = 0x4000000000;
	static const ULONGLONG ExportedType = 0x8000000000; static const ULONGLONG ManifestResource = 0x10000000000; 
	static const ULONGLONG NestedClass = 0x20000000000;static const ULONGLONG GenericParam = 0x40000000000; 
	static const ULONGLONG MethodSpec = 0x80000000000; static const ULONGLONG GenericParamConstraint = 0x100000000000;
};

#define ImgMdtStmMaskArrayLen 45

const ULONGLONG ImgMdtStmMaskArray[] = {
	ImgMdtStmMask::Module,ImgMdtStmMask::TypeRef,ImgMdtStmMask::TypeDef,
	ImgMdtStmMask::FieldPtr,ImgMdtStmMask::Field,ImgMdtStmMask::MethodPtr,
	ImgMdtStmMask::Method,ImgMdtStmMask::ParamPtr,ImgMdtStmMask::Param,
	ImgMdtStmMask::InterfaceImpl,ImgMdtStmMask::MemberRef,ImgMdtStmMask::Constant,
	ImgMdtStmMask::CustomAttribute,ImgMdtStmMask::FieldMarshal,ImgMdtStmMask::DeclSecurity,
	ImgMdtStmMask::ClassLayout,ImgMdtStmMask::FieldLayout,ImgMdtStmMask::StandAloneSig,
	ImgMdtStmMask::EventMap,ImgMdtStmMask::EventPtr,ImgMdtStmMask::Event,
	ImgMdtStmMask::PropertyMap,ImgMdtStmMask::PropertyPtr,ImgMdtStmMask::Property,
	ImgMdtStmMask::MethodSemantics,ImgMdtStmMask::MethodImpl,ImgMdtStmMask::ModuleRef,
	ImgMdtStmMask::TypeSpec,ImgMdtStmMask::ImplMap,ImgMdtStmMask::FieldRVA,
	ImgMdtStmMask::ENCLog,ImgMdtStmMask::ENCMap,ImgMdtStmMask::Assembly,
	ImgMdtStmMask::AssemblyProcessor,ImgMdtStmMask::AssemblyOS,ImgMdtStmMask::AssemblyRef,
	ImgMdtStmMask::AssemblyRefProcessor,ImgMdtStmMask::AssemblyRefOS,ImgMdtStmMask::File,
	ImgMdtStmMask::ExportedType,ImgMdtStmMask::ManifestResource,ImgMdtStmMask::NestedClass,
	ImgMdtStmMask::GenericParam,ImgMdtStmMask::MethodSpec,ImgMdtStmMask::GenericParamConstraint
};

IImgMdtTable* CreateMethodTable();

typedef enum __ImgMethodHdrType {
	tiny,fat,other
} ICMethodHdrType;

ICMethodHdrType GetMethodHeaderType(ImgMdtMethodHdr& mdtMethodHeader);


#define IMAGE_MDT_STREAM_SIGNATRUE_COMPRESSION "#~"
#define IMAGE_MDT_STREAM_SIGNATRUE	"#-"
typedef  IImgMdtTable* (*CREATE)(void);

const CREATE InstanceArray[] = {
	nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,CreateMethodTable,nullptr,nullptr,
};
*/
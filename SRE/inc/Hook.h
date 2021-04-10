#pragma once
#include <string>
#include <sredefs.h>
#include <MathPlus.h>


using std::wstring;
using std::string;


struct HABORIGIN {
	byte* fun_code;
	size_t code_size;

};

struct HCHIP {
	void_ptr hook_addr;
	HABORIGIN aborigin;
	void_ptr pedal_addr;
	size_t pedal_size;
};

HABORIGIN ReadFunCodeToHook(string opcode, void_ptr addr, HANDLE hProcess);

HCHIP RelaCallInstall(
	void_ptr tag,//跳转目标函数
	void_ptr hook_addr,	//hook地址
	bool idx_mode, //索引寄存器，true为esp,false为ebp
	Gauge param_offset,//参数相对索引寄存器的偏移
	Gauge param_amount,//需要的参数个数
	HANDLE hProcess=nullptr);

bool Unhook(HCHIP& data);



		

bool InjectLibrary(HANDLE process, wstring library);


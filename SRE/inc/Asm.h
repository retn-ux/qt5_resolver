#include <sredefs.h>
#include <capstone.h>
#include <XEDParse.h>
#include <vector>
#include <string>
using std::string;
using std::vector;

#define MACHINE_CODE_MAX_LENGTH 16

struct INSN {
	size_t size;
	uint64_t addr;
	string mnemonic;
	string op_str;
	byte machine_code[MACHINE_CODE_MAX_LENGTH];
};



size_t LengthDisasm(byte* buff, size_t buff_size, Gauge min_size, bool IsX64);
size_t Asm(string opcode, byte* out_buff, size_t out_buff_size, bool IsX64);
vector<INSN> Disasm(byte* in, size_t in_size, uint64_t base_addr, bool IsX64);
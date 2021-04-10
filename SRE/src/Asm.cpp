#include "pch.h"
#include <Asm.h>


size_t LengthDisasm(byte* buff, size_t buff_size, Gauge min_size, bool IsX64) {
	GUARD_GENTLE(min_size <= buff_size, 0);
	vector<INSN> ret;
	csh cs_handle;
	cs_insn* insn;
	cs_mode mode;
	mode = CS_MODE_32;
	if (IsX64) {
		mode = CS_MODE_64;
	}
	GUARD_GENTLE(cs_open(CS_ARCH_X86, mode, &cs_handle) == CS_ERR_OK, 0);
	const uint64_t base_addr = 0x1000;
	size_t count = 0;
	Gauge td = 0;
	count = cs_disasm(cs_handle, (byte*)buff, buff_size, base_addr, 0, &insn);
	if (count > 0) {
		for (size_t i = 0; i < count; i++) {
			td += insn[i].size;
			if (td >= min_size) {
				cs_free(insn, count);
				cs_close(&cs_handle);
				return td;
			}
		}
	}
	cs_free(insn, count);
	GUARD_SEVERE(cs_close(&cs_handle) == CS_ERR_OK);
	return 0;
}


size_t Asm(string opcode, byte* out_buff, size_t out_buff_size, bool IsX64) {
	XEDPARSE xed_base;
	ZeroMemory(&xed_base, sizeof(XEDPARSE));
	xed_base.x64 = IsX64;
	xed_base.cip = 0;
	memcpy(xed_base.instr, opcode.c_str(), opcode.size());
	XEDPARSE_STATUS statu = XEDParseAssemble(&xed_base);
	GUARD_GENTLE(statu == XEDPARSE_STATUS::XEDPARSE_OK, 0);
	if (out_buff == nullptr) return xed_base.dest_size;
	memcpy(out_buff, xed_base.dest, out_buff_size);
	return out_buff_size;
}


vector<INSN> Disasm(byte* in, size_t in_size, uint64_t base_addr, bool IsX64) {
	vector<INSN> ret;
	csh cs_handle;
	cs_insn* insn;
	cs_mode mode;
	mode = CS_MODE_32;
	if (IsX64) {
		mode = CS_MODE_64;
	}

	GUARD_GENTLE(cs_open(CS_ARCH_X86, mode, &cs_handle) == CS_ERR_OK, ret);
	size_t count = 0;
	count = cs_disasm(cs_handle, in, in_size, base_addr, 0, &insn);
	if (count > 0) {
		for (size_t i = 0; i < count; i++) {
			INSN m;
			m.addr = insn[i].address;
			m.mnemonic = insn[i].mnemonic;
			m.op_str = insn[i].op_str;
			m.size = insn[i].size;
			memcpy(m.machine_code, insn[i].bytes, MACHINE_CODE_MAX_LENGTH);
			ret.push_back(m);
		}
		cs_free(insn, count);
	}
	return ret;

}
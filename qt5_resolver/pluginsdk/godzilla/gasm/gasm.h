#ifndef _GODZILLA_GASM_GASM_H_
#define _GODZILLA_GASM_GASM_H_
#include <string>
#include <vector>

#include "godzilla.h"


#include "capstone.h"

#include "keystone.h"


size_t LengthDisasm(
	const csh& handle,
	const std::vector<Byte>& buffer,
	size_t expected_size
);


std::vector<Byte> Asm(
	ks_engine* handle,
	Fword baseAddress,
	const std::string& opcode
);

std::vector<cs_insn> Disasm(
	const csh& handle,
	Fword baseAddress,
	const std::vector<Byte>& buffer
);

#endif
#ifndef _GODZILLA_GMEMORY_GMEMORY_H_
#define _GODZILLA_GMEMORY_GMEMORY_H_

#include "godzilla.h"

bool ReadMemory(
	gpins_t ins, 
	Gauge address, 
	void* buffer, 
	size_t size
);


bool WriteMemory(
	gpins_t ins,
	Gauge address,
	const void* const buffer,
	size_t size
);

#endif
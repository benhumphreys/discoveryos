#ifndef CPUID_H
#define CPUID_H

#include "types.h"

struct cpuid {
	uint32_t stepping;
	uint32_t model;
	uint32_t family;
	uint32_t type;
};

struct cpuid get_cpuid(void);

#endif

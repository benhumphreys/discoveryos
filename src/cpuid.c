#include "cpuid.h"

struct cpuid get_cpuid(void) {
	struct cpuid cpuid;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t in = 1;

	__asm__("cpuid" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "a"(in));

	cpuid.stepping = a & 0xF;
	cpuid.model = (a >> 4) & 0xf;
	cpuid.family = (a >> 8) & 0xf;

	if (cpuid.family == 6 || cpuid.family == 15) {
		uint32_t ext_model = (a >> 16) & 0xf;
		cpuid.model |= (ext_model << 4);
		if (cpuid.family == 15) {
			uint32_t ext_family = (a >> 20) & 0xff;
			cpuid.family += ext_family;
		}
	}

	return cpuid;
}

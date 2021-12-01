#include "console.h"
#include "cpuid.h"

void kernel_main(void) {
	console_init();

    console_setcolor(VGA_COLOR_LIGHT_BLUE);
    console_printf("Welcome to Discovery OS\n");
    struct cpuid cpuid = get_cpuid();
    console_printf("CPU - Stepping: 0x%x Model: 0x%x Family: 0x%x\n",
            cpuid.stepping, cpuid.model, cpuid.family);
}

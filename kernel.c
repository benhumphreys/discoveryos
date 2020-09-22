#include "console.h"

void kernel_main(void) {
	console_init();

    console_setcolor(VGA_COLOR_LIGHT_BLUE);
	console_printf("Welcome to Discovery OS");
}

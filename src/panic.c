#include "panic.h"

#include "console.h"

static void halt() {
	while (1) {
		asm volatile("cli");
		asm volatile("hlt");
	}
}

void panic(const char *message) {
	console_printf("panic: ");
	console_printf(message);
	console_printf("\n");
	halt();
}

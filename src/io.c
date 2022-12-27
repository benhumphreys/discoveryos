#include "io.h"

#include "types.h"

void outb(uint16_t port, uint8_t data) {
	__asm__ __volatile__("outb %0,%1" : : "a"(data), "dN"(port));
}

uint8_t inb(uint16_t port) {
	uint8_t data;
	__asm__ __volatile__("inb %1,%0" : "=a"(data) : "dN"(port));
	return data;
}

void io_wait() {
	// Port 0x80 is used for BIOS POST codes; writing to it after boot should
	// not cause any problem
	outb(0x80, 0);
}

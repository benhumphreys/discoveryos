#include "io.h"

#include "types.h"

void outb(uint16_t port, uint8_t data) {
    __asm__ __volatile__ ("outb %0,%1" : : "a" (data), "dN" (port));
}

uint8_t inb(uint16_t port) {
    uint8_t data;
    __asm__ __volatile__ ("inb %1,%0"
            : "=a" (data)
            : "dN" (port));
    return data;
}

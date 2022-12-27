/*
 * 8253 Programmable Interval Timer (PIT)
 */
#include "pit.h"

#include "types.h"
#include "io.h"

// Ports
#define PORT_COUNTER0 0x40
#define PORT_CONTROL_WORD 0x43

// Control word
#define CONTROL_BINARY 0x0
#define CONTROL_BCD 0x1

#define CONTROL_MODE_0 0x0
#define CONTROL_MODE_1 0x2
#define CONTROL_MODE_2 0x3
#define CONTROL_MODE_3 0x6
#define CONTROL_MODE_4 0x8
#define CONTROL_MODE_5 0xA

#define CONTROL_LSB_ONLY 0x10
#define CONTROL_MSB_ONLY 0x20
#define CONTROL_LSB_THEN_MSB 0x30

#define CONTROL_COUNTER0 0x0
#define CONTROL_COUNTER1 0x40
#define CONTROL_COUNTER2 0x80

// Provides a 1ms interrupt interval
// The clock rate of 1193181.666 Hz is roughly 0.00083809 ms per pulse.
// 0.00083809 * 1193 is as close to 1ms as possible
#define COUNT_INIT 1193

void pit_init(void) {
	// Set binary counting, mode 3, load LSB first then MSB, counter 0
	outb(PORT_CONTROL_WORD, CONTROL_MODE_3 | CONTROL_LSB_THEN_MSB);

	uint32_t count = COUNT_INIT;
	outb(PORT_COUNTER0, count);
	outb(PORT_COUNTER0, count >> 8);
}

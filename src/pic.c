/*
 * 8259A Programmable Interrupt Controller (PIC)
 */
#include "pic.h"
#include "io.h"
#include "types.h"

// Ports
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

// Initialization command words
#define ICW1_ICW4 0x01 /* 1 = ICW4 needed, 0 = not needed */
#define ICW1_SINGLE 0x02 /* 1 = Single, 0 = cascade mode */
#define ICW1_INTERVAL4 0x04 /* Call address interval 1 = 4, 0 = 8 */
#define ICW1_LEVEL 0x08 /* 1 = Level triggered mode, 0 = edge triggered */
#define ICW1_INIT 0x10 /* Initialization */

#define ICW4_8086 0x01 /* 1 = 8086/88 mode, 0 = MCS-80/85 mode */
#define ICW4_AUTO_EOI 0x02 /* 1 = Auto EOI, 0 = Normal EOI */
#define ICW4_BUF_SLAVE 0x08 /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM 0x10 /* 1 = Special fully nested mode, 0 = not SFNM */

// Operation command words
#define PIC_EOI 0x20 /* End-of-interrupt command code */

/*
 * Remap interrupt vector offsets
 *
 * offset1 - Vector offset for PIC1 (master)
 * offset2 - Vector offset for PIC2 (slave)
 */
static void pic_remap(uint8_t offset1, uint8_t offset2) {
	// Store masks
	uint8_t a = inb(PIC1_DATA);
	uint8_t b = inb(PIC2_DATA);

	// Starts the initialization sequence (in cascade mode)
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	// ICW2 - Vector offsets for master and slave PIC
	outb(PIC1_DATA, offset1);
	io_wait();
	outb(PIC2_DATA, offset2);
	io_wait();
	// ICW3
	outb(PIC1_DATA, 4); // Tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2); // Tell Slave PIC its cascade identity (0000 0010)
	io_wait();
	// ICW4
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	// Restore saved masks
	outb(PIC1_DATA, a);
	outb(PIC2_DATA, b);
}

void pic_init(void) {
	pic_remap(0x20, 0x28);
}

void pic_send_eoi(uint8_t irq) {
	if (irq >= 8) {
		outb(PIC2_COMMAND, PIC_EOI);
	}

	outb(PIC1_COMMAND, PIC_EOI);
}

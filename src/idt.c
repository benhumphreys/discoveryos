#include "idt.h"
#include "types.h"
#include "interrupts.h"

#define IDT_NUM_DESCRIPTORS 256
#define IDT_INTERRUPT_GATE  0x8e // Type = 32-bit interrupt gate, DPL = 0, P = 1 
#define IDT_TRAP_GATE       0x8f // Type = 32-bit trap gate, DPL = 0, P = 1
#define IDT_TASK_GATE       0x85 // Type = 

struct idt_entry {
	uint16_t isr_low;   // Low 16 bits of the ISR function address
	uint16_t kernel_cs; // Code segment selector from GDT that will be loaded before calling the ISR
	uint8_t reserved;
	uint8_t attributes; // Types and attributes
	uint16_t isr_high;  // High 16 bits of the ISR function address
} __attribute__((packed));

struct idtr {
	uint16_t limit; // One less (one less entry that is) than the size of the IDT in bytes
	uint32_t base;  // The linear address of the IDT
} __attribute__((packed));

__attribute__((aligned(0x10))) 
static struct idt_entry idt[IDT_NUM_DESCRIPTORS];

static struct idtr idtr;

/*
 * Set an interrupt service routine for the given interrupt vector
 */
static void idt_set_descriptor(uint8_t vector, void *isr, uint8_t attributes) {
    struct idt_entry* descriptor = &idt[vector];
    descriptor->isr_low        = (uint32_t)isr & 0xffff;
    descriptor->kernel_cs      = 0x8; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->reserved       = 0;
    descriptor->attributes     = attributes;
    descriptor->isr_high       = (uint32_t)isr >> 16;
}

void idt_init(void) {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(struct idt_entry) * IDT_NUM_DESCRIPTORS - 1;

    // Setup exception ISRs (0-31) - See: https://wiki.osdev.org/Exceptions
    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, &default_exception_handler, IDT_TRAP_GATE);
    }

    __asm__ __volatile__ ("lidt %0" : : "m"(idtr));
    __asm__ __volatile__ ("sti"); // Set interrupt flag (enable non-maskable interrupts)
}

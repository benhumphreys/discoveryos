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

    idt_set_descriptor(0, &exception_handler_isr0, IDT_TRAP_GATE);
    idt_set_descriptor(1, &exception_handler_isr1, IDT_TRAP_GATE);
    idt_set_descriptor(2, &exception_handler_isr2, IDT_INTERRUPT_GATE);
    idt_set_descriptor(3, &exception_handler_isr3, IDT_TRAP_GATE);
    idt_set_descriptor(4, &exception_handler_isr4, IDT_TRAP_GATE);
    idt_set_descriptor(5, &exception_handler_isr5, IDT_TRAP_GATE);
    idt_set_descriptor(6, &exception_handler_isr6, IDT_TRAP_GATE);
    idt_set_descriptor(7, &exception_handler_isr7, IDT_TRAP_GATE);
    idt_set_descriptor(8, &exception_handler_isr8, IDT_TRAP_GATE);
    idt_set_descriptor(9, &exception_handler_isr9, IDT_TRAP_GATE);
    idt_set_descriptor(10, &exception_handler_isr10, IDT_TRAP_GATE);
    idt_set_descriptor(11, &exception_handler_isr11, IDT_TRAP_GATE);
    idt_set_descriptor(12, &exception_handler_isr12, IDT_TRAP_GATE);
    idt_set_descriptor(13, &exception_handler_isr13, IDT_TRAP_GATE);
    idt_set_descriptor(14, &exception_handler_isr14, IDT_TRAP_GATE);
    idt_set_descriptor(15, &exception_handler_isr15, IDT_TRAP_GATE);
    idt_set_descriptor(16, &exception_handler_isr16, IDT_TRAP_GATE);
    idt_set_descriptor(17, &exception_handler_isr17, IDT_TRAP_GATE);
    idt_set_descriptor(18, &exception_handler_isr18, IDT_TRAP_GATE);
    idt_set_descriptor(19, &exception_handler_isr19, IDT_TRAP_GATE);
    idt_set_descriptor(20, &exception_handler_isr20, IDT_TRAP_GATE);
    idt_set_descriptor(21, &exception_handler_isr21, IDT_TRAP_GATE);
    idt_set_descriptor(22, &exception_handler_isr22, IDT_TRAP_GATE);
    idt_set_descriptor(23, &exception_handler_isr23, IDT_TRAP_GATE);
    idt_set_descriptor(24, &exception_handler_isr24, IDT_TRAP_GATE);
    idt_set_descriptor(25, &exception_handler_isr25, IDT_TRAP_GATE);
    idt_set_descriptor(26, &exception_handler_isr26, IDT_TRAP_GATE);
    idt_set_descriptor(27, &exception_handler_isr27, IDT_TRAP_GATE);
    idt_set_descriptor(28, &exception_handler_isr28, IDT_TRAP_GATE);
    idt_set_descriptor(29, &exception_handler_isr29, IDT_TRAP_GATE);
    idt_set_descriptor(30, &exception_handler_isr30, IDT_TRAP_GATE);
    idt_set_descriptor(31, &exception_handler_isr31, IDT_TRAP_GATE);

    __asm__ __volatile__ ("lidt %0" : : "m"(idtr));
    __asm__ __volatile__ ("sti"); // Set interrupt flag (enable non-maskable interrupts)
}

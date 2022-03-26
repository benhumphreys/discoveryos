#include "interrupts.h"
#include "console.h"

static void halt() {
    asm volatile("cli");
    asm volatile("hlt");
};

__attribute__((interrupt))
void exception_handler_isr0(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (Divide-by-zero error)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr1(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (Debug)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr2(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (NMI)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr3(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (Breakpoint)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr4(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (Overflow)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr5(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (Bound Range Exceeded)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr6(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (Invalid Opcode)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr7(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (Device Not Available)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr8(struct interrupt_frame *frame __attribute__((unused)), uint32_t error_code) {
    console_printf("Unhandled exception (Double Fault) - Error code 0x%x\n", error_code);
    halt();
}

__attribute__((interrupt))
void exception_handler_isr9(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (Coprocessor Segment Overrun)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr10(struct interrupt_frame *frame __attribute__((unused)), uint32_t error_code) {
    console_printf("Unhandled exception (Invalid TSS) - Error code 0x%x\n", error_code);
    halt();
}

__attribute__((interrupt))
void exception_handler_isr11(struct interrupt_frame *frame __attribute__((unused)), uint32_t error_code) {
    console_printf("Unhandled exception (Segment Not Present) - Error code 0x%x\n", error_code);
    halt();
}

__attribute__((interrupt))
void exception_handler_isr12(struct interrupt_frame *frame __attribute__((unused)), uint32_t error_code) {
    console_printf("Unhandled exception (Stack-Segment Fault) - Error code 0x%x\n", error_code);
    halt();
}

__attribute__((interrupt))
void exception_handler_isr13(struct interrupt_frame *frame __attribute__((unused)), uint32_t error_code) {
    console_printf("Unhandled exception (General Protection Fault) - Error code 0x%x\n", error_code);
    halt();
}

__attribute__((interrupt))
void exception_handler_isr14(struct interrupt_frame *frame __attribute__((unused)), uint32_t error_code) {
    console_printf("Unhandled exception (Page Fault) - Error code 0x%x\n", error_code);
    halt();
}

__attribute__((interrupt))
void exception_handler_isr15(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (15)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr16(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (x87 Floating Point Exception)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr17(struct interrupt_frame *frame __attribute__((unused)), uint32_t error_code) {
    console_printf("Unhandled exception (Alignment Check) - Error code 0x%x\n", error_code);
    halt();
}

__attribute__((interrupt))
void exception_handler_isr18(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (Machine Check)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr19(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (SIMD Floating-Point Exception)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr20(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (Virtulization Exception)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr21(struct interrupt_frame *frame __attribute__((unused)), uint32_t error_code) {
    console_printf("Unhandled exception (Control Protection Exceoption) - Error code 0x%x\n", error_code);
    halt();
}

__attribute__((interrupt))
void exception_handler_isr22(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (22)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr23(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (23)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr24(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (24)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr25(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (25)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr26(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (26)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr27(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (27)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr28(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (Hypervisor Injection Exception)");
    halt();
}

__attribute__((interrupt))
void exception_handler_isr29(struct interrupt_frame *frame __attribute__((unused)), uint32_t error_code) {
    console_printf("Unhandled exception (VMM Communication Exception) - Error code 0x%x\n", error_code);
    halt();
}

__attribute__((interrupt))
void exception_handler_isr30(struct interrupt_frame *frame __attribute__((unused)), uint32_t error_code) {
    console_printf("Unhandled exception (Security Exception) - Error code 0x%x\n", error_code);
    halt();
}

__attribute__((interrupt))
void exception_handler_isr31(struct interrupt_frame *frame __attribute__((unused))) {
    console_printf("Unhandled exception (31)");
    halt();
}

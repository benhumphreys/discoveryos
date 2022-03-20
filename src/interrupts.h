#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "types.h"

struct interrupt_frame {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t sp;
    uint32_t ss;
} __attribute__((packed));

__attribute__((interrupt))
void exception_handler_isr0(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr1(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr2(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr3(struct interrupt_frame *frame);
__attribute__((interrupt))

__attribute__((interrupt))
void exception_handler_isr4(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr5(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr6(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr7(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr8(struct interrupt_frame *frame, uint32_t error_code);

__attribute__((interrupt))
void exception_handler_isr9(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr10(struct interrupt_frame *frame, uint32_t error_code);

__attribute__((interrupt))
void exception_handler_isr11(struct interrupt_frame *frame, uint32_t error_code);
__attribute__((interrupt))

__attribute__((interrupt))
void exception_handler_isr12(struct interrupt_frame *frame, uint32_t error_code);

__attribute__((interrupt))
void exception_handler_isr13(struct interrupt_frame *frame, uint32_t error_code);

__attribute__((interrupt))
void exception_handler_isr14(struct interrupt_frame *frame, uint32_t error_code);

__attribute__((interrupt))
void exception_handler_isr15(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr16(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr17(struct interrupt_frame *frame, uint32_t error_code);

__attribute__((interrupt))
void exception_handler_isr18(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr19(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr20(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr21(struct interrupt_frame *frame, uint32_t error_code);

__attribute__((interrupt))
void exception_handler_isr22(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr23(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr24(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr25(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr26(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr27(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr28(struct interrupt_frame *frame);

__attribute__((interrupt))
void exception_handler_isr29(struct interrupt_frame *frame, uint32_t error_code);

__attribute__((interrupt))
void exception_handler_isr30(struct interrupt_frame *frame, uint32_t error_code);

__attribute__((interrupt))
void exception_handler_isr31(struct interrupt_frame *frame);

/*
__attribute__((interrupt))
void default_interrupt_handler(struct interrupt_frame *frame);
*/

#endif

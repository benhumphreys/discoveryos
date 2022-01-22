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
void default_exception_handler(struct interrupt_frame *frame, uint32_t error_code);

/*
__attribute__((interrupt))
void default_interrupt_handler(struct interrupt_frame *frame);
*/

#endif

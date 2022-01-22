#include "interrupts.h"
#include "console.h"

__attribute__((interrupt))
void default_exception_handler(struct interrupt_frame *frame, uint32_t error_code) {
    console_printf("Handled exception (Default handler) - Error code 0x%x\n", error_code);
    while (1) {
    }
    // TODO: For any ISRs that take an error code and then return (i.e. iret), the error
    // code must be popped off the stack
}

/*
__attribute__((interrupt)) void default_interrupt_handler(struct interrupt_frame *frame) {
    console_printf("Handled interrupt (Default handler)\n");
    while (1) {
    }
}
*/

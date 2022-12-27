#ifndef PIC_H
#define PIC_H

#include "types.h"

/* Initialize the PIC */
void pic_init();

/* Send end-of-interrupt */
void pic_send_eoi(uint8_t irq);

#endif

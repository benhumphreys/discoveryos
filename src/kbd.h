#ifndef KBD_H
#define KBD_H

#include "types.h"

/* Bit settings for key_stroke.modifiers */
#define CTRL_MODIFIER 0x1
#define ALT_MODIFIER 0x2

struct key_stroke {
	// Key pressed, after SHIFT modifier applied
	char c;

	// Modifier key bit field (ctrl, alt)
	uint8_t modifiers;
};

/* Returns the next ASCII character in the output buffer */
struct key_stroke kbd_poll(void);

#endif

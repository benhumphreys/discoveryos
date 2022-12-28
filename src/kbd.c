/*
 * 8042 Keyboard Controller Driver
 */
#include "kbd.h"

#include "io.h"

#define NKEYS 83
#define KEY_RELEASE_MASK 0x80
#define SCAN_CODE_MASK 0x7f

// IO Ports
#define KBD_OUTPUT_BUFFER_PORT 0x60
#define KBD_INPUT_BUFFER_PORT 0x60
#define KBD_STATUS_REG_PORT 0x64
#define KBD_CONTROL_REG_PORT 0x64

// Scan codes
#define SCAN_CODE_LEFT_SHIFT 42
#define SCAN_CODE_RIGHT_SHIFT 54

static int left_shift_depressed = 0;
static int right_shift_depressed = 0;

// Map scan code to ASCII character
char to_ascii[NKEYS + 1] = {
	0, // Not used
	27, // ESC
	'1',  '2', '3', '4', '5', '6', '7', '8', '9', '0', '-',	 '=',
	'\b', // Backspace
	'\t', // Tab
	'q',  'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[',	 ']', '\n',
	0, // CTRL
	'a',  's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	0, // Left shift
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
	0, // Right shift
	0, // Print screen
	0, // Alt
	' ', // Space
	0, // Caps
	0, // F1
	0, // F2
	0, // F3
	0, // F4
	0, // F5
	0, // F6
	0, // F7
	0, // F8
	0, // F9
	0, // F10
	0, // Num lock
	0, // Scroll lock
	0, // Home
	0, // Up
	0, // Page up
	'-', // Numpad minus
	0, // Left arrow
	0, // Centre key numpad (5)
	0, // Right arrow
	'+', // Numpad plus
	0, // End
	0, // Down
	0, // Page down
	0, // Insert
	0 // Delete
};

static void handle_shift(uint8_t code, uint8_t release) {
	if (code == SCAN_CODE_LEFT_SHIFT) {
		left_shift_depressed = release ? 0 : 1;
	}
	if (code == SCAN_CODE_RIGHT_SHIFT) {
		right_shift_depressed = release ? 0 : 1;
	}
}

static char toupper(char ch) {
	if (ch < 'a' || ch > 'z') {
		return ch;
	}
	return ch - ('a' - 'A');
}

char kbd_poll(void) {
	while (1) {
		uint8_t status = 0;
		do {
			status = inb(KBD_STATUS_REG_PORT);
			if ((status & 1) == 0) {
				// Will be woken by all interrupts including the 1ms timer, but
				// is better than pure fast polling
				asm volatile("hlt");
			}
		} while ((status & 1) == 0);

		uint8_t output = inb(KBD_OUTPUT_BUFFER_PORT);
		uint8_t release = output & KEY_RELEASE_MASK;
		uint8_t code = output & SCAN_CODE_MASK;

		if (code == SCAN_CODE_LEFT_SHIFT || code == SCAN_CODE_RIGHT_SHIFT) {
			handle_shift(code, release);
		}

		if (release) {
			continue;
		}
		if (code > 0 && code <= NKEYS && to_ascii[code] > 0) {
			if (left_shift_depressed || right_shift_depressed) {
				return toupper(to_ascii[code]);
			} else {
				return to_ascii[code];
			}
		}
	}
}

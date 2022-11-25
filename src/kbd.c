/*
 * 8042 Keyboard Controller Driver
 */
#include "kbd.h"

#include "io.h"
#include "console.h"

#define NKEYS 83
#define KBD_DATA_PORT 0x60
#define KBD_STATUS_PORT 0x64

char scan_code[NKEYS + 1] = {
    0,      // Not used
    27,     // ESC
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '-', '=',
    '\b',   // Backspace
    '\t',   // Tab
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
    '[', ']',
    '\n',
    0,      // CTRL
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    ';', '\'', '`',
    0,      // Left shift
    '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm',
    ',', '.', '/',
    0,      // Right shift
    0,      // Print screen
    0,      // Alt
    ' ',    // Space
    0,      // Caps
    0,      // F1
    0,      // F2
    0,      // F3
    0,      // F4
    0,      // F5
    0,      // F6
    0,      // F7
    0,      // F8
    0,      // F9
    0,      // F10
    0,      // Num lock
    0,      // Scroll lock
    0,      // Home
    0,      // Up
    0,      // Page up
    '-',    // Numpad minus
    0,      // Left arrow
    0,      // Centre key numpad (5)
    0,      // Right arrow
    '+',    // Numpad plus
    0,      // End
    0,      // Down
    0,      // Page down
    0,      // Insert
    0       // Delete  
};

char kbd_poll(void) {
    uint8_t status = 0;
    do {
        status = inb(KBD_STATUS_PORT);
        if (status & 0x80) {
            // Key release
            continue;
        }
    } while ((status & 1) == 0);

    uint8_t code = inb(KBD_DATA_PORT);
    if (code > 0 && code <= NKEYS) {
        return scan_code[code];
    } else {
        return 0;
    }
}

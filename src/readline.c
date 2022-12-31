/*
 * Provides basic readline style functionality
 *
 * Shortcuts supported:
 * - Backspace - Delete previous character
 * - Ctrl + u - Cut text to beginning of line
 */
#include "readline.h"

#include "kbd.h"
#include "kmalloc.h"
#include "console.h"
#include "string.h"

#define INITIAL_CAPACITY 32

static char *grow(char *buf, size_t newsize) {
	char *newbuf = kmalloc(newsize);
	memmove(newbuf, buf, newsize);
	kfree(buf);
	return newbuf;
}

char *readline(void) {
	char *buf = kmalloc(INITIAL_CAPACITY);
	size_t capacity = INITIAL_CAPACITY;
	size_t size = 0; // Index to next character to write

	struct key_stroke key_event;
	while (1) {
		key_event = kbd_poll();
		if (key_event.c == '\n') {
			break;
		}
		if (key_event.c == '\b') {
			if (size > 0) {
				console_backspace(1);
				size--;
			}
			continue;
		}
		if (key_event.c == 'u' && (key_event.modifiers & CTRL_MODIFIER)) {
			console_backspace(size);
			size = 0;
			continue;
		}
		if (size == capacity - 1) {
			capacity *= 2;
			buf = grow(buf, capacity);
		}
		buf[size++] = key_event.c;
		console_printf("%c", key_event.c);
	};

	buf[size] = '\0';
	return buf;
}

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

	char c;
	while (1) {
		c = kbd_poll();
		if (c == '\n') {
			break;
		}
        if (c == '\b') {
            if (size > 0) {
                console_backspace(1);
                size--;
            }
            continue;
        }
		if (size == capacity - 1) {
			capacity *= 2;
			buf = grow(buf, capacity);
		}
		buf[size++] = c;
		console_printf("%c", c);
	};

	buf[size] = '\0';
	return buf;
}

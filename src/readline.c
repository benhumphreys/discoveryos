#include "readline.h"

#include "kbd.h"
#include "kmalloc.h"
#include "console.h"

#define BUF_SIZE 256

char *readline(void) {
	char *buf = kmalloc(BUF_SIZE);
	size_t capacity = BUF_SIZE;
	size_t size = 0; // Index to next character to write

	char c;
	do {
		c = kbd_poll();
		if (c == '\n') {
			break;
		}
		buf[size++] = c;
		console_printf("%c", c);
	} while (size < capacity - 1);

	buf[size] = '\0';
	return buf;
}

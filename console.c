#include "console.h"

#include "types.h"
#include "stdarg.h"
#include "string.h"

/* The VGA video memory address. */
#define VIDEO_MEM 0xB8000

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
static size_t console_row;
static size_t console_column;
static uint8_t console_color;
static uint16_t* video_mem;
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
void console_init(void) {
	console_row = 0;
	console_column = 0;
	console_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	video_mem = (uint16_t*) VIDEO_MEM;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			video_mem[index] = vga_entry(' ', console_color);
		}
	}
}
 
void console_setcolor(uint8_t color) {
	console_color = color;
}
 
static void console_putcharat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	video_mem[index] = vga_entry(c, color);
}
 
static void console_putchar(char c) {
    if (c == '\0') {
        return;
    }
    if (c == '\n') {
        console_column = 0;
        console_row++;
        return;
    }

	console_putcharat(c, console_color, console_column, console_row);
	if (++console_column == VGA_WIDTH) {
		console_column = 0;
		if (++console_row == VGA_HEIGHT) {
			console_row = 0;
        }
	}
}

static void console_write(const char *data, size_t size) {
	for (size_t i = 0; i < size; i++) {
		console_putchar(data[i]);
    }
}

static void console_putuint32(uint32_t n) {
    char buf[11];
    memset(buf, 0, 11);

    int i = 0;
    // Generate digits in reverse order
    do {
        buf[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    reverse(buf);
    console_write(buf, 11);
}

void console_printf(const char *format, ...) {
    va_list argp;
    va_start(argp, format);

    for (int i = 0; format[i]; i++) {
        if (format[i] != '%') {
            console_putchar(format[i]);
        } else {
            i++;
            switch (format[i]) {
                case 'd':
                    uint32_t val = va_arg(argp, uint32_t);
                    console_putuint32(val);
                    break;
                default:
                    console_putchar(format[i + 1]);
            }
        }
    }

    va_end(argp);
}

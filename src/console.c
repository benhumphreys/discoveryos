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
static volatile uint16_t *video_mem;
 
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
 
static void console_scroll(void) {
    volatile uint16_t *d = video_mem;
    volatile uint16_t *s = &video_mem[VGA_WIDTH];
    int n = (VGA_WIDTH - 1) * VGA_HEIGHT * 2;
    if (d < s) {
        while (n--) {
            *d++ = *s++;
        }
    }

    // Clear the bottom row
    uint16_t blank = vga_entry(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    size_t rowStart = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for (size_t col = 0; col < VGA_WIDTH; col++) {
        video_mem[rowStart + col] = blank;
    }
}

static void console_putchar(char c) {
    if (c == '\n') {
        console_column = 0;
        console_row++;
    } else {
        console_putcharat(c, console_color, console_column, console_row);
        if (++console_column == VGA_WIDTH) {
            console_column = 0;
            console_row++;
        }
    }

    if (console_row == VGA_HEIGHT) {
        console_scroll();
        console_row = VGA_HEIGHT - 1;
    }
}

static void console_write(const char *data, size_t size) {
	for (size_t i = 0; i < size && data[i] != '\0'; i++) {
		console_putchar(data[i]);
    }
}

static void console_putuint32(uint32_t n, uint32_t base) {
    if (base < 2) {
        return;
    }

    const int MAX_DIGITS = 32;
    char buf[MAX_DIGITS];
    memset(buf, 0, MAX_DIGITS);

    int i = 0;
    // Generate digits in reverse order
    do {
        uint32_t digit = n % base;
        char ascii_offset = (base > 10 && digit >= 10) ? 'A' - 10 : '0';
        buf[i++] = digit + ascii_offset;
    } while ((n /= base) > 0);

    reverse(buf);
    console_write(buf, MAX_DIGITS);
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
                    console_putuint32(va_arg(argp, uint32_t), 10);
                    break;
                case 'x':
                    console_putuint32(va_arg(argp, uint32_t), 16);
                    break;
                default:
                    console_putchar(format[i + 1]);
            }
        }
    }

    va_end(argp);
}

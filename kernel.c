#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* The VGA video memory address. */
#define VIDEO_MEM 0xB8000

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t console_row;
size_t console_column;
uint8_t console_color;
uint16_t* video_mem;
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len]) {
		len++;
    }
	return len;
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
 
void console_putcharat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	video_mem[index] = vga_entry(c, color);
}
 
void console_putchar(char c) {
	console_putcharat(c, console_color, console_column, console_row);
	if (++console_column == VGA_WIDTH) {
		console_column = 0;
		if (++console_row == VGA_HEIGHT) {
			console_row = 0;
        }
	}
}
 
void console_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++) {
		console_putchar(data[i]);
    }
}
 
void console_printf(const char* data) {
	console_write(data, strlen(data));
}
 
void kernel_main(void) {
	console_init();

    console_setcolor(VGA_COLOR_LIGHT_BLUE);
	console_printf("Welcome to Discovery OS");
}

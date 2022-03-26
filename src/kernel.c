#include "console.h"
#include "cpuid.h"
#include "multiboot.h"
#include "gdt.h"
#include "idt.h"

static void print_multibootinfo(struct multiboot_info *info) {
    console_printf("Multiboot Info:\n");
    if (info->flags & MULTIBOOT_INFO_FLAG_MEMORY) {
        console_printf("  Mem lower: %d KB\n", info->mem_lower);
        console_printf("  Mem upper: %d KB\n", info->mem_upper);
    }
    if (info->flags & MULTIBOOT_INFO_FLAG_BOOTDEV) {
        console_printf("  Boot device - Disk: %x, Part1: %x, Part2: %x, Part3: %x\n",
                (info->boot_device >> 24) & 0xFF,
                (info->boot_device >> 16) & 0xFF,
                (info->boot_device >> 8) & 0xFF,
                info->boot_device & 0xFF);
    }
}

void kernel_main(uint32_t multiboot_magic, struct multiboot_info *multiboot_info) {
	console_init();
    console_setcolor(VGA_COLOR_LIGHT_BLUE);
    console_printf("Welcome to Discovery OS\n");
    print_multibootinfo(multiboot_info);

    if (multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        console_printf("Invalid magic number: 0x%x\n", (unsigned) multiboot_magic);
        return;
    }

    gdt_init();
    idt_init();

    struct cpuid cpuid = get_cpuid();
    console_printf("CPU - Stepping: 0x%x Model: 0x%x Family: 0x%x\n",
            cpuid.stepping, cpuid.model, cpuid.family);
    asm("int $0xe"); // Software interrupt (Page Fault)
}

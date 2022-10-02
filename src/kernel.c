#include "console.h"
#include "cpuid.h"
#include "multiboot.h"
#include "gdt.h"
#include "idt.h"
#include "kmalloc.h"

static void print_multibootinfo(struct multiboot_info *info) {
    console_printf("Multiboot Info:\n");
    if (info->flags & MULTIBOOT_INFO_FLAG_MEMORY) {
        console_printf("Mem lower: %d KB\n", info->mem_lower);
        console_printf("Mem upper: %d KB\n", info->mem_upper);
    }
    if (info->flags & MULTIBOOT_INFO_FLAG_BOOTDEV) {
        console_printf("Boot device - Disk: %x, Part1: %x, Part2: %x, Part3: %x\n",
                (info->boot_device >> 24) & 0xFF,
                (info->boot_device >> 16) & 0xFF,
                (info->boot_device >> 8) & 0xFF,
                info->boot_device & 0xFF);
    }
    if (info->flags & MULTIBOOT_INFO_MEM_MAP) {

      console_printf("mmap_addr = 0x%x, mmap_length = 0x%x\n",
              (uint32_t) info->mmap_addr, (uint32_t) info->mmap_length);

      for (struct multiboot_mmap_entry *mmap = (struct multiboot_mmap_entry *) info->mmap_addr;
              (uint32_t) mmap < info->mmap_addr + info->mmap_length;
              mmap = (struct multiboot_mmap_entry *) ((uint32_t) mmap + mmap->size + sizeof (mmap->size))) {
          console_printf("  base_addr = 0x%x %x, length = 0x%x %x, type = 0x%x\n",
                  (uint32_t) (mmap->addr >> 32),
                  (uint32_t) (mmap->addr & 0xffffffff),
                  (uint32_t) (mmap->len >> 32),
                  (uint32_t) (mmap->len & 0xffffffff),
                  (uint32_t) mmap->type);
      }

    }
}

static void init_mm(struct multiboot_info *info) {
    for (struct multiboot_mmap_entry *mmap = (struct multiboot_mmap_entry *) info->mmap_addr;
              (uint32_t) mmap < info->mmap_addr + info->mmap_length;
              mmap = (struct multiboot_mmap_entry *) ((uint32_t) mmap + mmap->size + sizeof (mmap->size))) {
        // No support for RAM > 4GB yet
        if (mmap->addr > 0xffffffff || mmap->addr + mmap->len > 0xffffffff) {
            return;
        }
        uint32_t addr = mmap->addr & 0xffffffff;
        uint32_t len = mmap->len & 0xffffffff;
        if (addr >= 0x100000 && mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
            // Kernel is loaded at 0x100000 (i.e. 1M) so reserve from 1M to 4M for it
            if (addr < 0x400000) {
                addr = 0x400000;
                len -= 0x400000 - addr;
            }
            kmalloc_init((void *) addr, len);
        }
    }
}

void kernel_main(uint32_t multiboot_magic, struct multiboot_info *multiboot_info) {
	console_init();
    console_setcolor(VGA_COLOR_LIGHT_BLUE);
    console_printf("Welcome to Discovery OS\n");
    print_multibootinfo(multiboot_info);
    init_mm(multiboot_info);

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

#include "gdt.h"
#include "types.h"

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_descriptor {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct gdt_entry gdt[3] __attribute__ ((aligned(0x1000)));
struct gdt_descriptor gdt_p;
extern void load_gdt(struct gdt_descriptor *gdt_p);

void set_gdt_entry(uint32_t idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[idx].base_low = (base & 0xffff);
    gdt[idx].base_middle = (base >> 16) & 0xff;
    gdt[idx].base_high = (base >> 24) & 0xff;

    gdt[idx].limit_low = (limit & 0xffff);
    gdt[idx].granularity = ((limit >> 16) & 0x0f);

    gdt[idx].granularity |= (granularity & 0xf0);
    gdt[idx].access = access;
}

void gdt_init(void) {
    // Null descriptor (offset: 0x0)
    set_gdt_entry(0, 0, 0, 0, 0);

    // Kernel code (offset: 0x8)
    set_gdt_entry(1, 0, 0xffffffff, 0x9a, 0xcf);

    // Kernel data (offset:010)
    set_gdt_entry(2, 0, 0xffffffff, 0x92, 0xcf);

    // Load GDT register
    gdt_p.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdt_p.base = (uint32_t) &gdt;

    load_gdt(&gdt_p);
}

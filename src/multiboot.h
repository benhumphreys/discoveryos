#ifndef MULTIBOOT_T
#define MULTIBOOT_T

#include "types.h"

#define MULTIBOOT_BOOTLOADER_MAGIC      0x2BADB002

#define MULTIBOOT_INFO_FLAG_MEMORY      0x1
#define MULTIBOOT_INFO_FLAG_BOOTDEV     0x2
#define MULTIBOOT_INFO_FLAG_CMDLINE     0x4
#define MULTIBOOT_INFO_FLAG_MODS        0x8
#define MULTIBOOT_INFO_AOUT_SYMS        0x10
#define MULTIBOOT_INFO_ELF_SHDR         0X20
#define MULTIBOOT_INFO_MEM_MAP          0x40

/* mmap_entry types */
#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE       3
#define MULTIBOOT_MEMORY_NVS                    4
#define MULTIBOOT_MEMORY_BADRAM                 5

/* The symbol table for a.out. */
struct multiboot_aout_symbol_table {
  uint32_t tabsize;
  uint32_t strsize;
  uint32_t addr;
  uint32_t reserved;
};

/* The section header table for ELF. */
struct multiboot_elf_section_header_table {
  uint32_t num;
  uint32_t size;
  uint32_t addr;
  uint32_t shndx;
};

struct multiboot_mmap_entry {
  uint32_t size;
  uint64_t addr;
  uint64_t len;
  uint32_t type;
} __attribute__((packed));

struct multiboot_info {
  /* Multiboot info version number */
  uint32_t flags;

  /* Available memory from BIOS */
  uint32_t mem_lower;
  uint32_t mem_upper;

  /* Boot partition */
  uint32_t boot_device;

  /* Kernel command line */
  uint32_t cmdline;

  /* Boot-Module list */
  uint32_t mods_count;
  uint32_t mods_addr;

  union {
    struct multiboot_aout_symbol_table aout_sym;
    struct multiboot_elf_section_header_table elf_sec;
  } u;

  /* Memory Mapping buffer */
  uint32_t mmap_length;
  uint32_t mmap_addr;
};

#endif

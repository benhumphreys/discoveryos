#ifndef MULTIBOOT_T
#define MULTIBOOT_T

#include "types.h"

#define MULTIBOOT_BOOTLOADER_MAGIC      0x2BADB002

#define MULTIBOOT_INFO_FLAG_MEMORY      0x1
#define MULTIBOOT_INFO_FLAG_BOOTDEV     0x2
#define MULTIBOOT_INFO_FLAG_CMDLINE     0x4
#define MULTIBOOT_INFO_FLAG_MODS        0x8

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
};

#endif

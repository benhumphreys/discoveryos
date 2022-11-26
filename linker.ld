/* Linker script - See https://sourceware.org/binutils/docs-2.33.1/ld/index.html */

ENTRY(_start)
 
SECTIONS
{
    /* Start sections at 1 MByte */
    . = 1M;

    /* Put multiboot header first so the boot loader can find it */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }
 
    /* Read-only data */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }
 
    /* Read-write data (initialized) */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }
 
    /* Read-write data (uninitialized) and stack */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    /* Don't include these sections */
    /DISCARD/ :
    {
        *(.eh_frame)
    }
} 

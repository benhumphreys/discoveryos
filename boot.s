#
# Constants for the multiboot header
#

# Loaded boot modules must be aligned on page (4KB) boundaries
.set ALIGN,    1<<0

# Provide memory map
.set MEMINFO,  1<<1

# The field ‘flags’ specifies features that the OS image requests or requires of an boot loader
.set FLAGS,    ALIGN | MEMINFO

# The field ‘magic’ is the magic number identifying the header
.set MAGIC,    0x1BADB002

# The field ‘checksum’ is a 32-bit unsigned value which, when added to the other magic field
# (i.e. ‘magic’ and ‘flags’), must have a 32-bit unsigned sum of zero.
.set CHECKSUM, -(MAGIC + FLAGS)

# Multiboot header
# See: https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Setup stack (grows downwards)
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
 
# Entry point
.section .text
.global _start
.type _start, @function
_start:

	mov $stack_top, %esp
 
	call kernel_main

# Clear interrupt flag then infinite loop
	cli
1:	hlt
	jmp 1b
 
.size _start, . - _start

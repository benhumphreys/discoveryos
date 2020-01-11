.code16                 # 16 bit code generation
.text

.global _start

_start:
   movw $0x07c0, %ax    # Setup the data segment register
   movw %ax, %ds        # (Can't set %ds directly)
   movw $msg, %si

ch_loop:
   lodsb                # Loads byte at address %ds:%si into %al
   or %al, %al          # Detect end of string
   jz hang
   mov $0x0e, %ah       # Function code for teletype output
   int $0x10            # BIOS interrupt
   jmp ch_loop

hang:
   jmp hang

msg:
.asciz "Welcome to Discovery OS."

.org 510                # The boot sector is 512 bytes in length
.word 0xAA55            # And must end with 0xAA55

.section .text

.global load_gdt
.type load_gdt, @function
load_gdt:
.code32
    mov 0x4(%esp), %eax
    lgdt (%eax)
    mov $0x10, %ax      # Set data segments
    mov %ax, %ss
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    ljmp $0x08, $end    # Set code segment
end:
    ret

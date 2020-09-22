cat << EOF > script.gdb
add-symbol-file boot.o
add-symbol-file kernel.o
target remote | qemu-system-i386 -S -gdb stdio -kernel discoveryos-kernel
EOF

gdb -x script.gdb

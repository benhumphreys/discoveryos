cat << EOF > script.gdb
add-symbol-file stage1.o 0x7c00
target remote | qemu-system-i386 -S -gdb stdio -drive file=floppy.img,format=raw,index=0,media=disk
EOF

gdb -x script.gdb

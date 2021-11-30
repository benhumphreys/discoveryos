GDB_SCRIPT=build/script.gdb
rm -f $GDB_SCRIPT

for F in `find build -name '*.o'`; do
    echo "add-symbol-file  $F" >> $GDB_SCRIPT
done

echo "target remote | qemu-system-i386 -S -gdb stdio -kernel discoveryos-kernel" >> $GDB_SCRIPT

gdb -x $GDB_SCRIPT

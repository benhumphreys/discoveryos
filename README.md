# Discovery OS

A toy operating system.

Currently a bootloader is not included. Fortunatly QEMU provides a start mode where
it will load a multiboot kernel.

## Running the operating system

We run the operating system inside [QEMU](https://www.qemu.org/). On an Ubuntu
system it can be installed like so:
```
apt-get install qemu
```

To run DiscoveryOS in QEMU without debugging:
```
make run
```

To run in QEMU with GDB:
```
make debug
```
Then press 'c' to continue execution, as QEMU/GDB will started in a paused state.

## Notes

- Kernel image is loaded at 0x100000 (1M) and address range 1-4M
is reserved for the kernel

## References

* [Multiboot specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html)
* [GNU Linker documentation](https://sourceware.org/binutils/docs-2.33.1/ld/index.html)
* [GNU Compiler inline assembly](https://gcc.gnu.org/onlinedocs/gcc/Using-Assembly-Language-with-C.html)
  * [Machine specific constraints](https://gcc.gnu.org/onlinedocs/gcc/Machine-Constraints.html#Machine-Constraints)

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

## References

* [Multiboot specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html)
* [GNU Linker documentation](https://sourceware.org/binutils/docs-2.33.1/ld/index.html)

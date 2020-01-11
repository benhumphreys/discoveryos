AS := as
CC := gcc
LD := ld

all: discoveryos.bin

discoveryos.bin: kernel.o boot.o
	ld -m elf_i386 -T linker.ld kernel.o boot.o -o discoveryos.bin -nostdlib
	grub-file --is-x86-multiboot discoveryos.bin

kernel.o: kernel.c
	$(CC) -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: boot.s
	$(AS) --32 boot.s -o boot.o

.PHONY: clean
clean:
	rm -f *.o *.bin

.PHONY: run
run: discoveryos.bin
	scripts/discoveryos-run.sh

.PHONY: debug
debug: discoveryos.bin
	scripts/discoveryos-debug.sh

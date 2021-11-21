AS := as
CC := gcc
LD := ld

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
OBJS = boot.o string.o console.o kernel.o

KERNEL = discoveryos-kernel

all: $(KERNEL)

$(KERNEL): $(OBJS)
	ld -m elf_i386 -T linker.ld $(OBJS) -o $(KERNEL) -nostdlib
	grub-file --is-x86-multiboot $(KERNEL)

%.o: %.c %.h
	$(CC) -m32 -c -o $@ $< $(CFLAGS)

boot.o: boot.s
	$(AS) --32 boot.s -o boot.o

.PHONY: clean
clean:
	rm -f *.o $(KERNEL)

.PHONY: run
run: $(KERNEL)
	scripts/discoveryos-run.sh

.PHONY: debug
debug: $(KERNEL)
	scripts/discoveryos-debug.sh

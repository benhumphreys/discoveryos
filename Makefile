AS := as
LD := ld

all:	floppy.img

floppy.img:	stage1.bin
		dd if=/dev/zero of=$@ bs=512 count=2880
		dd if=$< of=$@ conv=notrunc seek=0

stage1.bin:	stage1.s
		$(AS) --32 -o stage1.o $<
		$(LD) -m elf_i386 -Ttext 0x0 --oformat binary --entry=0x0 -o $@ stage1.o

clean:
		rm -f *.o *.bin floppy.img

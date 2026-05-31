CC = gcc
ASM = nasm
LD = ld

CFLAGS = -ffreestanding -nostdlib -m64 -I.

all: arsenos.iso

mouse.o: mouse.c
	$(CC) -c mouse.c -o mouse.o $(CFLAGS)

kernel.bin: boot.o mouse.o
	$(LD) -T linker.ld -o kernel.bin boot.o mouse.o

boot.o: boot.asm
	$(ASM) -f elf64 boot.asm -o boot.o

arsenos.iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/
	echo 'menuentry "ArsenOS" { multiboot2 /boot/kernel.bin }' > iso/boot/grub/grub.cfg
	grub-mkrescue -o arsenos.iso iso/

clean:
	rm -rf *.o *.bin iso arsenos.iso

run: arsenos.iso
	qemu-system-x86_64 -cdrom arsenos.iso -netdev user,id=net0 -device e1000,netdev=net0

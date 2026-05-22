CC = x86_64-elf-gcc
ASM = nasm
CFLAGS = -ffreestanding -nostdlib -nostartfiles -m64 -Iinclude
LDFLAGS = -T linker.ld -ffreestanding -nostdlib -lgcc

all: kernel.bin

boot.o: boot.asm
	$(ASM) -f elf64 boot.asm -o boot.o

kernel.o: kernel.c
	$(CC) -c kernel.c -o kernel.o $(CFLAGS)

kernel.bin: boot.o kernel.o
	$(CC) -o kernel.bin boot.o kernel.o $(LDFLAGS)

clean:
	rm -f *.o *.bin

run: kernel.bin
	qemu-system-x86_64 -kernel kernel.bin -m 128

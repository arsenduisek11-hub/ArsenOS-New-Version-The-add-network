CC = x86_64-elf-gcc
CFLAGS = -ffreestanding -nostdlib -m64 -I.
LDFLAGS = -T linker.ld -ffreestanding -nostdlib

all: arsenos.iso

mouse.o: mouse.c
	$(CC) -c mouse.c -o mouse.o $(CFLAGS)

cursor.o: cursor.c
	$(CC) -c cursor.c -o cursor.o $(CFLAGS)

wm.o: window_manager.c
	$(CC) -c window_manager.c -o wm.o $(CFLAGS)

browser.o: browser.c
	$(CC) -c browser.c -o browser.o $(CFLAGS)

terminal.o: terminal_app.c
	$(CC) -c terminal_app.c -o terminal.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

kernel.bin: mouse.o cursor.o wm.o browser.o terminal.o main.o
	$(CC) -o kernel.bin $^ $(LDFLAGS)

arsen_terminal: arsen_terminal.c
	gcc arsen_terminal.c -o arsen_terminal

arsenos.iso: kernel.bin arsen_terminal
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/
	cp arsen_terminal iso/boot/
	echo "menuentry 'ArsenOS' { multiboot2 /boot/kernel.bin }" > iso/boot/grub/grub.cfg
	grub-mkrescue -o arsenos.iso iso

clean:
	rm -f *.o *.bin arsen_terminal arsenos.iso
	rm -rf iso

run: arsenos.iso
	qemu-system-x86_64 -cdrom arsenos.iso -m 256 -usb -device usb-tablet

gdb: arsenos.iso
	qemu-system-x86_64 -cdrom arsenos.iso -s -S -m 256

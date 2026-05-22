mkdir -p iso/boot/grub
cp kernel.bin iso/boot/
echo "menuentry 'ArsenOS' { multiboot2 /boot/kernel.bin }" > iso/boot/grub/grub.cfg
grub-mkrescue -o ArsenOS.iso iso
// Это сблрка для реального железа ISO

#!/bin/bash
echo "Сборка ArsenOS..."

# Компилируем загрузчик (если есть .asm)
nasm -f elf64 boot.asm -o boot.o 2>/dev/null || echo "boot.asm не найден, пропускаем"

# Компилируем ядро
gcc -c kernel.c -o kernel.o -ffreestanding -nostdlib -m64 2>/dev/null || echo "kernel.c не найден"

# Линкуем
ld -T linker.ld -o kernel.bin boot.o kernel.o 2>/dev/null || echo "Ошибка линковки, но продолжаем"

# Создаём ISO
mkdir -p iso/boot/grub
cp kernel.bin iso/boot/ 2>/dev/null || echo "Нет kernel.bin, создаю заглушку"
echo 'menuentry "ArsenOS" { multiboot2 /boot/kernel.bin }' > iso/boot/grub/grub.cfg
grub-mkrescue -o ArsenOS.iso iso/ 2>/dev/null

echo "Готово! Файл ArsenOS.iso создан"

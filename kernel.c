// Это ядро минимальное by arsen
#include <stdint.h>
#include <stddef.h>

#define VGA_ADDR 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static uint16_t* vga = (uint16_t*)VGA_ADDR;
static int cursor_x = 0, cursor_y = 0;

static uint8_t color = 0x0A;

void putchar(char c) {
    if(c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        vga[cursor_y * VGA_WIDTH + cursor_x] = (color << 8) | c;
        cursor_x++;
    }
    if(cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    if(cursor_y >= VGA_HEIGHT) {
        // скролл сделаю потом
        cursor_y = VGA_HEIGHT - 1;
    }
}

void print(const char* str) {
    for(int i = 0; str[i]; i++) putchar(str[i]);
}

void clear() {
    for(int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        vga[i] = 0x0700 | ' ';
    cursor_x = cursor_y = 0;
}

void kmain() {
    clear();
    print("ArsenOS v2.0\n");
    print("[+] Kernel loaded\n");
    print("[+] Entering GUI mode\n");
    
    while(1) {
        __asm__("hlt");
    }
}

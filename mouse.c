#include <stdint.h>

#define MOUSE_PORT 0x60
#define STATUS_PORT 0x64

typedef struct {
    int x, y;
    int dx, dy;
    int left, right, middle;
    int ready;
} MouseEvent;

MouseEvent mouse_event;
int mouse_x = 400, mouse_y = 300;
int mouse_cycle = 0;
uint8_t mouse_byte[3];

void mouse_wait() {
    for(int i = 0; i < 100000; i++) __asm__("pause");
}

void mouse_write(uint8_t val) {
    mouse_wait();
    __asm__("outb %0, %1" : : "a"(val), "d"((uint16_t)0x64));
}

uint8_t mouse_read() {
    mouse_wait();
    uint8_t val;
    __asm__("inb %1, %0" : "=a"(val) : "d"((uint16_t)0x60));
    return val;
}

void mouse_init() {
    mouse_write(0xA8);
    mouse_write(0x20);
    mouse_wait();
    uint8_t status = mouse_read();
    status |= 2;
    mouse_write(0x60);
    mouse_write(status);
    mouse_write(0xD4);
    mouse_write(0xF4);
    mouse_read();
}

void mouse_handle() {
    uint8_t status;
    __asm__("inb %1, %0" : "=a"(status) : "d"((uint16_t)0x64));
    
    if(!(status & 0x21)) return;
    
    uint8_t data = mouse_read();
    
    if(mouse_cycle == 0) {
        if((data & 0x08) == 0) return;
        mouse_byte[0] = data;
        mouse_cycle++;
    } else if(mouse_cycle == 1) {
        mouse_byte[1] = data;
        mouse_cycle++;
    } else if(mouse_cycle == 2) {
        mouse_byte[2] = data;
        
        mouse_event.dx = mouse_byte[1];
        mouse_event.dy = mouse_byte[2];
        
        if(mouse_byte[0] & 0x10) mouse_event.dx |= 0xFFFFFF00;
        if(mouse_byte[0] & 0x20) mouse_event.dy |= 0xFFFFFF00;
        
        mouse_event.dy = -mouse_event.dy;
        
        mouse_x += mouse_event.dx;
        mouse_y += mouse_event.dy;
        
        if(mouse_x < 0) mouse_x = 0;
        if(mouse_x > 1024) mouse_x = 1024;
        if(mouse_y < 0) mouse_y = 0;
        if(mouse_y > 768) mouse_y = 768;
        
        mouse_event.left = mouse_byte[0] & 0x01;
        mouse_event.right = mouse_byte[0] & 0x02;
        mouse_event.middle = mouse_byte[0] & 0x04;
        mouse_event.ready = 1;
        
        mouse_cycle = 0;
    }
}

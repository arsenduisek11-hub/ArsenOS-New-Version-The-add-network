#include <stdint.h>

uint32_t* framebuffer = (uint32_t*)0xFFFFFFFF80000000;
uint8_t keyboard_buf[256];
int shift_pressed = 0;

void main() {
    mouse_init();
    wm_init();
    
    int term_win = wm_create_window("Terminal", 100, 100, 600, 400);
    int browser_win = wm_create_window("ArsenBrowser", 150, 150, 800, 500);
    
    browser_init();
    
    while(1) {
        mouse_handle();
        wm_handle_mouse(mouse_event.left, mouse_x, mouse_y);
        
        for(int i = 0; i < 1024 * 768; i++) {
            framebuffer[i] = 0x2A2A3A;
        }
        
        wm_render(framebuffer);
        draw_cursor(mouse_x, mouse_y, framebuffer, 1024);
        
        __asm__("hlt");
    }
}
/ интеграция всегс

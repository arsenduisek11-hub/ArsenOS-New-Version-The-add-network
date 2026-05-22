#include <stdint.h>

#define MAX_WINDOWS 16

typedef struct {
    int x, y, w, h;
    int active;
    char title[64];
    void (*draw)(void*);
    void* data;
} Window;

Window windows[MAX_WINDOWS];
int win_count = 0;
int active_win = -1;

int mouse_x = 0, mouse_y = 0;
int drag_win = -1;
int drag_off_x, drag_off_y;

void wm_init() {
    for(int i = 0; i < MAX_WINDOWS; i++) {
        windows[i].active = 0;
    }
}

int wm_create_window(const char* title, int x, int y, int w, int h) {
    if(win_count >= MAX_WINDOWS) return -1;
    
    windows[win_count].x = x;
    windows[win_count].y = y;
    windows[win_count].w = w;
    windows[win_count].h = h;
    windows[win_count].active = 1;
    win_count++;
    active_win = win_count - 1;
    
    return win_count - 1;
}

void wm_handle_mouse(int btn, int x, int y) {
    if(drag_win != -1) {
        if(btn == 0) {
            drag_win = -1;
        } else {
            windows[drag_win].x = x - drag_off_x;
            windows[drag_win].y = y - drag_off_y;
        }
        return;
    }
    
    if(btn == 1) {
        for(int i = win_count - 1; i >= 0; i--) {
            Window* w = &windows[i];
            if(x >= w->x && x <= w->x + w->w && y >= w->y && y <= w->y + 20) {
                if(active_win != i) {
                    for(int j = 0; j < win_count; j++) windows[j].active = 0;
                    windows[i].active = 1;
                    active_win = i;
                }
                drag_win = i;
                drag_off_x = x - w->x;
                drag_off_y = y - w->y;
                break;
            }
        }
    }
}

void wm_render(uint32_t* fb) {
    for(int i = 0; i < win_count; i++) {
        Window* w = &windows[i];
        
        for(int y = 0; y < w->h; y++) {
            for(int x = 0; x < w->w; x++) {
                int px = w->x + x;
                int py = w->y + y;
                if(px >= 0 && px < 1024 && py >= 0 && py < 768) {
                    if(y < 20) fb[py * 1024 + px] = 0x2A6DFF;
                    else fb[py * 1024 + px] = 0xF0F0F0;
                }
            }
        }
    }
}
// it's window manager It's easy and 😝

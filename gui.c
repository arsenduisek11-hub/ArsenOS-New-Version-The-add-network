// Оконная система GUI математика ин пайтон
#include <stdint.h>

#define WIDTH 1024
#define HEIGHT 768

static uint32_t* fb = (uint32_t*)0xFFFFFFFF80000000;

typedef struct {
    int x, y, w, h;
    int active;
    char title[64];
} Window;

Window windows[16];
int win_count = 0;

void putpixel(int x, int y, uint32_t color) {
    if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        fb[y * WIDTH + x] = color;
}

void draw_rect(int x, int y, int w, int h, uint32_t color) {
    for(int i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
            putpixel(x + i, y + j, color);
}

int create_window(const char* title, int w, int h) {
    if(win_count >= 16) return -1;
    windows[win_count].x = 100;
    windows[win_count].y = 100;
    windows[win_count].w = w;
    windows[win_count].h = h;
    windows[win_count].active = 1;
    win_count++;
    return win_count - 1;
}

void render() {
    for(int i = 0; i < win_count; i++) {
        Window* w = &windows[i];
        draw_rect(w->x, w->y, w->w, w->h, 0xFFFFFF);
        draw_rect(w->x, w->y, w->w, 20, 0x2A6DFF);
    }
}

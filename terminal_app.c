#include <stdint.h>

char term_buf[4096];
int term_buf_len = 0;
int term_cursor = 0;

void term_putchar(char c, uint32_t* fb, int x, int y) {
    // изичный шрифт 8x8
    (void)fb; (void)x; (void)y;
}

void term_handle_input(char c) {
    if(c == '\n') {
        term_buf[term_buf_len] = 0;
        
        if(strcmp(term_buf, "help") == 0) {
            // вывод помощи
        } else if(strcmp(term_buf, "ars") == 0) {
            // запуск ArsenScript
        } else if(strcmp(term_buf, "exit") == 0) {
            // закрыть окно терминала
        }
        
        term_buf_len = 0;
        term_cursor = 0;
    } else if(c == '\b') {
        if(term_buf_len > 0) term_buf_len--;
    } else {
        if(term_buf_len < 4095) term_buf[term_buf_len++] = c;
    }
}

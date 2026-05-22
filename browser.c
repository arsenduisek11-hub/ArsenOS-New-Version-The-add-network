#include <stdint.h>

char url_buf[256];
int url_len = 0;
char page_content[65536];

void browser_draw_text(const char* text, uint32_t* fb, int x, int y) {
    // рендеринг текста в окне имбы
    (void)fb; (void)x; (void)y;
}

void browser_go(const char* url) {
    char req[512];
    snprintf(req, sizeof(req), "GET / HTTP/1.0\r\nHost: %s\r\n\r\n", url);
    
    int sock = net_connect(url, 80);
    if(sock < 0) return;
    
    net_send(sock, req, strlen(req));
    int len = net_recv(sock, page_content, sizeof(page_content) - 1);
    page_content[len] = 0;
    net_close(sock);
    
    // простейший парсинг — убираем теги
    char* out = page_content;
    int in_tag = 0;
    for(int i = 0; page_content[i]; i++) {
        if(page_content[i] == '<') in_tag = 1;
        else if(page_content[i] == '>') in_tag = 0;
        else if(!in_tag && page_content[i] != '\n' && page_content[i] != '\r') {
            *out++ = page_content[i];
        }
    }
    *out = 0;
}

void browser_init() {
    browser_go("google.com");
}
// это текстовый браузер может не работать или да хз

// Сетевой стек допишу когда будет ноут 
#include <stdint.h>

typedef struct {
    uint8_t mac[6];
    uint32_t ip;
} NetDev;

NetDev nic;

void send_packet(uint8_t* data, int len) {
    // RTL8139 драйвер напишу когда ноут будет
    (void)data; (void)len;
}

int ping(uint32_t ip) {
    print("ping ");
    // туду
    return 0;
}

char* http_get(const char* url) {
    print("HTTP GET ");
    return NULL;
}

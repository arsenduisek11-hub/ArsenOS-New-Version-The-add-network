// it's Interpretation by ars
#include <stdint.h>
#include <stddef.h>

typedef struct {
    char* name;
    void* value;
    int type;
} Var;

Var vars[256];
int var_count = 0;

typedef struct {
    char* name;
    void (*func)(void*);
} Builtin;

void gui_window(void* args) {
    print("[GUI] creating window\n");
}

void net_http(void* args) {
    print("[NET] HTTP request\n");
}

Builtin builtins[] = {
    {"gui.window", gui_window},
    {"net.http", net_http},
    {NULL, NULL}
};

void eval(const char* code) {
    // парсер сделаю потом
    print("executing ArsenScript...\n");
}

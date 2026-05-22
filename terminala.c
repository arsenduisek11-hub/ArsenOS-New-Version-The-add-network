// arsen_terminal.c
// сам терминал с ArsenScript внутри

#include <stdio.h>
#include <string.h>

char* commands[] = {"help", "ls", "cat", "run", "ars", "exit", NULL};

void exec_ars(const char* code) {
    // вызов интерпретатора ArsenScript
    printf(">>> %s\n", code);
}

int main(int argc, char** argv) {
    char input[256];
    
    printf("ArsenTerminal v1.0\n");
    printf("Type 'ars <code>' to run ArsenScript\n");
    
    while(1) {
        printf("$> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if(strcmp(input, "exit") == 0) break;
        else if(strncmp(input, "ars ", 4) == 0) exec_ars(input + 4);
        else if(strcmp(input, "help") == 0) printf("ars, help, exit\n");
        else printf("unknown\n");
    }
    
    return 0;
}

#include <stddef.h>

char input[256];
int input_len = 0;

void cmd_help() {
    print("help, clear, ls, cat, ping, run, gui\n");
}

void cmd_ls() {
    ls();
}

void cmd_ping(char* arg) {
    print("ping ");
    print(arg);
    print("\n");
}

void process_command(char* cmd) {
    if(strcmp(cmd, "help") == 0) cmd_help();
    else if(strcmp(cmd, "ls") == 0) cmd_ls();
    else if(strncmp(cmd, "ping ", 5) == 0) cmd_ping(cmd + 5);
    else print("unknown command\n");
}
// Файловая система допишу когда будет ноуто

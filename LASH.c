#include <stdio.h>
#include "LASH.h"

void execute_command(char *command) {
    if (strcmp(command, "help") == 0) {
        help();
    } else {
        printf("LASH: Unknown command: %s\n", command);
    }
}

int main() {

    char input[100];
    printf("Welcome to LASH 1.0.0\n\n");

    printf("root@LASH:~$ ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    execute_command(input);

    return 0;
}
#ifndef LASH_H
#define LASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
    printf("Usage: lash [options] [command]\n");
    printf("Options:\n");
    printf("  -h, --help      Show this help message and exit\n");
    printf("  -v, --version   Show version information and exit\n");
    printf("Commands:\n");
    printf("  run             Run the specified command\n");
}

void print(char *input[]) {
    printf("%s", input[0]);
}

#endif /* LASH_H */
#ifndef LASH_H
#define LASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
    printf("Usage: lash [command]\n");
    
}

void print(char *input) {
    printf("%s\n", input);
}

#endif /* LASH_H */
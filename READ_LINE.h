#ifndef READ_LINE_H
#define READ_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_line(void) {
    size_t size = 64;      // initial buffer size
    size_t len = 0;        // current length of data

    char *buf = (char*) malloc(size);
    if (!buf) return NULL;

    while (1) {
        // read into the remaining space
        if (!fgets(buf + len, size - len, stdin)) {
            // EOF or read error
            if (len == 0) {
                free(buf);
                return NULL;
            }
            return buf; // return what we have
        }

        len += strlen(buf + len);

        // if newline found, line is complete
        if (len > 0 && buf[len - 1] == '\n') {
            return buf;
        }

        // no newline → need more space
        size_t new_size = size * 2;
        char *newbuf = (char*) realloc(buf, new_size);
        if (!newbuf) {
            free(buf);
            return NULL;
        }

        buf = newbuf;
        size = new_size;
    }
}

#endif // READ_LINE_H


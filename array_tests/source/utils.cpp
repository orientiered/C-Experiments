#include <stdio.h>
#include "utils.h"

void swap(void *a, void *b, size_t size) {
    char *ac = (char*) a, *bc = (char*) b;
    char c = 0;
    while (size--) {
        c = *ac;
        *ac++ = *bc;
        *bc++ = c;
    }
}

void flushScanfBuffer() {
    int c = 0;
    while ((c = getchar()) != '\n' && c != '\0' && c != EOF){}
}

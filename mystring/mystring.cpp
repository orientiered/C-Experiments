#include <stddef.h>
#include "mystring.h"
//#include <string.h>
char *strcpy(char *s, const char *ct) {
    char *s_copy = s;
    while (*s++=*ct++);
    return s_copy;
}

char *strncpy(char *s, const char *ct, size_t n) {
    char *s_copy = s;
    while (n && (*s++ = *ct++))n--;
    if (!n) *s = '\0';
    return s_copy;
}

char *strcat(char *s, const char *ct) {
    char *s_copy = s;
    while (*s) s++;
    while (*s++ = *ct++);
    return s_copy;
}

char *strncat(char *s, const char *ct, size_t n) {
    char *s_copy = s;
    while (*s) s++;
    while (n && (*s++ = *ct++)) n--;
    if (n) *s = '\0';
    return s_copy;
}

int strcmp(const char *s, const char *t) {
    for (; *s || *t; s++, t++) {
        if (*s > *t) return 1;
        else if (*s < *t) return -1;
    }
    return 0;
}

int strncmp(const char *s, const char *t, size_t n) {
    for (;n &&  (*s || *t); s++, t++, n--) {
        if (*s > *t) return 1;
        else if (*s < *t) return -1;
    }
}

char *strchr(char *s, char c) {
    while (*s != c && *s) s++;
    if (*s == c)
        return s;
    else
        return NULL;
}

char *strrchr(char *s, char c) {
    const char *start = s;
    while (*s) s++;
    while (*s != c && s > start) --s;
    if (*s == c) return s;
    else NULL;
}



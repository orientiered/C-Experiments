#include <stddef.h>
#include <stdio.h>
#include "mystring.h"
//#include <string.h>
char *strcpy(char *s, const char *ct) {
    char *s_copy = s;
    while ((*s++=*ct++) != '\0');
    return s_copy;
}

char *strncpy(char *s, const char *ct, size_t n) {
    char *s_copy = s;
    while (n && (*s++ = *ct++) != '\0')n--;
    if (!n) *s = '\0';
    return s_copy;
}

char *strcat(char *s, const char *ct) {
    char *s_copy = s;
    while (*s) s++;
    while ((*s++ = *ct++) != '\0');
    return s_copy;
}

char *strncat(char *s, const char *ct, size_t n) {
    char *s_copy = s;
    while (*s) s++;
    while (n && (*s++ = *ct++) != '\0') n--;
    if (!n) *s = '\0';
    return s_copy;
}

int strcmp(const char *s, const char *t) {
    for (; *s || *t; s++, t++) {
        if (*s != *t)
            return int(*s) - *t;
    }
    return 0;
}

int strncmp(const char *s, const char *t, size_t n) {
    for (;n &&  (*s || *t); s++, t++, n--) {
        if (*s != *t)
            return int(*s) - *t;
    }
    return 0;
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
    if (*s == c)
        return s;
    else
        return NULL;
}

char *strstr(char *s, const char *t) {
    while (*s) {
        while ((*s != *t) && *s)
            s++;
        char *sCopy = s;
        while ((*s == *t) && *s && *t)
            s++, t++;
        if (*t == '\0')
            return sCopy;
        else
            t -= s - sCopy;
    }
    return NULL;
}

char *strtok(char *s, const char *tok) {

}



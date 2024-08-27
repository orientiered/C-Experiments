#ifndef MY_STRING_H
#define MY_STRING_H

char *strcpy(char *s, const char *ct);
char *strncpy(char *s, const char *ct, size_t n);

char *strcat(char *s, const char *ct);
char *strncat(char *s, const char *ct, size_t n);

int strcmp(const char *s, const char *t);
int strncmp(const char *s, const char *t, size_t n);

char *strchr(const char *s, char c);
char *strrchr(const char *s, char c);

#endif

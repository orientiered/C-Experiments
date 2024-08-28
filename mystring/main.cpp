#include <stdio.h>

#include "mystring.h"

int main() {
    char str1[100] = "Hello world\n";
    char str2[] = "Aboba\n";

    strncpy(str1, str2, 1);
    printf("%s", str1);
    return 0;
}

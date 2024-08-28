#include <stdio.h>
//#include<string.h>
#include "mystring.h"

int main() {
    char str1[] = "Hello world\n";
    char str2[] = "world";

    //strncpy(str1, str2, 1);
    printf("%d", strstr(str1, str2) - str1);
    return 0;
}

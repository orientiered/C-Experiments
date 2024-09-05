#include <stdio.h>
//#include<string.h>
#include "mystring.h"

#include <sys/mman.h>
#include <unistd.h>

void ded();
void strstrTester();

int main() {
    strstrTester();
    return 0;
}

void strstrTester() {
    char s1[1000] = {};
    char s2[1000] = {};
    do {
        fgets(s1, 1000, stdin);
        fgets(s2, 1000, stdin);
        s2[strlen(s2)-1] = '\0'; //cutting \n at the end
        const char *p = strstr(s1, s2);
        if (p == NULL) printf("Can't find s2 in s1\n");
        else {
            printf("%s", s1);
            int index = p - s1;
            for (int i = 0; i < index; i++)
                printf(" ");
            printf("^\n");
            for (int i = 0; i < index; i++)
                printf(" ");
            printf("%d\n", index);
        }
    } while (strlen(s1) > 0 && strlen(s2) > 0);
}
void ded() {
    void* dedPtr = (void*)"DED KRUT";
    const long PAGE_SIZE = sysconf(_SC_PAGESIZE);
    void* dedPtrStart = (void*) ((long int)dedPtr & ~(PAGE_SIZE-1));
    if (mprotect(dedPtrStart, 1000, PROT_WRITE) != 0)
        printf("Error in mprotect\n");
    strcpy("DED KRUT", "DED LOH");

    printf("DED KRUT");
}

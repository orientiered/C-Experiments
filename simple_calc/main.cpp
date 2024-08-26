//Calculator
#include <stdio.h>
#include "solver.h"

#define MAXSIZE 1000

int main(int argc, char *argv[]) {

    char *eq = (char*) malloc(MAXSIZE);
    double result;
    *eq = '\0';
    if (argc != 1) {
        while (--argc) {
            strcat(eq, *++argv);
            strcat(eq, " ");
        }
        strcat(eq, "\n");
        result = solve(eq);
        printf("%g\n", result);
    } else while (fgets(eq, MAXSIZE, stdin) != NULL) {
        result = solve(eq);
        printf("%g\n", result);
    }
    free(eq);
    return 0;
}

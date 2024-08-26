#include "stack.h"
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_OP_SIZE 100
#define DBG
#undef DBG
double solve(char *eq);
char *get_op_word(char *start, char *op); //записывает слово из массива start в массив op, возвращает указатель на позицию сразу после слова либо null, если конец строки

double solve (char *eq) {
    #ifdef DBG
        printf("Entered solve\n");
        printf("Processing string %s\n", eq);
    #endif
    Stack st;
    char op_word[MAX_OP_SIZE];
    char *str = eq;
    while ( (str = get_op_word(str, op_word)) != NULL) {
        #ifdef DBG
                printf("Processing word %s\n", op_word);
        #endif
        if (isdigit(op_word[0]) || (op_word[0] == '-' || op_word[0] == '+') && isdigit(op_word[1])) {
            st.push(atof(op_word));
            #ifdef DBG
                printf("Processed digit %g\n", st.top());
            #endif
        } else {
            double op2;
            switch(op_word[0]) {
            case '+':
                st.push(st.pop() + st.pop());
                break;
            case '*':
                st.push(st.pop() * st.pop());
                break;
            case '-':
                op2 = st.pop();
                st.push(st.pop() - op2);
                break;
            case '/':
                op2 = st.pop();
                assert(op2);
                st.push(st.pop() / op2);
                break;
            case '%':
                op2 = st.pop();
                assert(op2);
                st.push(fmod(st.pop(), op2));
                break;
            case '?':
                printf("%g\n", st.top());
                break;
            case '.':
                st.push(st.top());
                break;
            default:
                if (!strcmp(op_word, "sin")) {
                    st.push(sin(st.pop()));
                } else if (!strcmp(op_word, "cos")) {
                    st.push(cos(st.pop()));
                } else if (!strcmp(op_word, "exp")) {
                    st.push(exp(st.pop()));
                } else if (!strcmp(op_word, "pow")) {
                    op2 = st.pop();
                    st.push(pow(st.pop(), op2));
                }
                break;
            }
            #ifdef DBG
                printf("Processed op %s\n", op_word);
            #endif
        }
    }
    return st.pop();
}

char *get_op_word(char *start, char *op) {
    if (*start == '\n' || *start == '\0') return NULL;
    while (isspace(*start) && *start != '\n' && *start != '\0') start++;
    while (!isspace(*start)) *op++ = *start++;
    *op = '\0';
    return start;
}

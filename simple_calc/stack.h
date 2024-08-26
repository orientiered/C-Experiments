#define BASESIZE 10
#include <assert.h>

typedef struct stack{
    double *st = NULL;
    int size = 0, reserved = 0;

    void push(double num) {
        if (st == NULL) {
            st = (double *) malloc(BASESIZE * sizeof(double));
            reserved = BASESIZE;
        }

        if (size >= reserved) {
            double *new_st = (double *) malloc(reserved * 3 * sizeof(double) / 2);
            for (int i = 0; i < size; i++) new_st[i] = st[i];
            free(st);
            st = new_st;
            reserved = reserved * 3 / 2;
        }

        st[size++] = num;
    }

    double pop() {
        //printf("Popped %g, size %d\n", st[size-1], size);
        assert(size);
        if (size == 0) return 0;
        return st[--size];
    }

    double top() {
        return st[size-1];
    }
    void clear() {
        free(st);
        size = 0;
        st = (double *) malloc(BASESIZE * sizeof(double));
        reserved = BASESIZE;
    }

} Stack;

#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix {
    int *data;
    size_t sizeX, sizeY;
} matrix_t;

matrix_t createMatrix(size_t sizeX, size_t sizeY);

matrix_t addMatrix(const matrix_t mat1, const matrix_t mat2);

void fillMatrix(matrix_t mat, const int filler);

void delMatrix(matrix* mat);

void printMatrix(const matrix_t mat);
#endif

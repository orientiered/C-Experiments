#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix {
    int *data;
    size_t sizeX, sizeY;
} matrix_t;

matrix_t createMatrix(size_t sizeX, size_t sizeY);

matrix_t addMatrix(const matrix_t mat1, const matrix_t mat2);

matrix_t multiplyMatrix(const matrix_t mat1, const matrix_t mat2);

matrix_t copyMatrix(const matrix_t mat);

matrix_t inverse(const matrix_t mat);

long long complement(matrix_t mat, matrix_t temp, size_t y, size_t x);

int* getElement(matrix_t mat, size_t i, size_t j);

long long det(const matrix_t mat);

void fillMatrix(matrix_t mat, const int filler);

void setMatrix(matrix_t mat, const int* arr);

void delMatrix(matrix* mat);

void printMatrix(const matrix_t mat);
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "matrix.h"

matrix_t createMatrix(size_t sizeX, size_t sizeY) {
    matrix_t newMatrix = {};
    newMatrix.data = (int*) calloc(sizeX*sizeY, sizeof(int));
    if (newMatrix.data) {
        newMatrix.sizeX = sizeX;
        newMatrix.sizeY = sizeY;
    }
    return newMatrix;
}

matrix_t addMatrix(matrix_t mat1, const matrix_t mat2) {
    assert(mat1.sizeX == mat2.sizeX);
    assert(mat1.sizeY == mat2.sizeY);

    assert(mat1.data);
    assert(mat2.data);

    matrix_t sum = createMatrix(mat1.sizeX, mat1.sizeY);

    for (size_t i = 0; i < mat1.sizeX*mat1.sizeY; i++)
        sum.data[i] = mat1.data[i] + mat2.data[i];

    return sum;
}


void fillMatrix(matrix_t mat, const int filler) {
    assert(mat.data);

    for (size_t i = 0; i < mat.sizeX*mat.sizeY; i++)
        mat.data[i] = filler;

}

void delMatrix(matrix* mat) {
    if (mat->data)
        free(mat->data);
}

void printMatrix(const matrix_t mat) {
    if (!mat.data) return;

    for (size_t i = 0; i < mat.sizeY; i++) {
        for (size_t j = 0; j < mat.sizeX; j++) {
            printf("%d ", mat.data[i*mat.sizeX+j]);
        }
        printf("\n");
    }

}


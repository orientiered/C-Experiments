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

matrix_t multiplyMatrix(const matrix_t mat1, const matrix_t mat2) {
    assert(mat1.sizeX == mat2.sizeY);

    matrix_t result = createMatrix(mat2.sizeX, mat1.sizeY);

    for (size_t i = 0; i < result.sizeY; i++) {
        for (size_t j = 0; j < result.sizeX; j++) {
            for (size_t k = 0; k < mat1.sizeX; k++)
                result.data[i*result.sizeX+j] +=
                    mat1.data[i*mat1.sizeX + k] * mat2.data[k*mat2.sizeX + j];
        }
    }
    return result;
}

matrix_t copyMatrix(const matrix_t mat) {
    matrix_t newMatrix = createMatrix(mat.sizeX, mat.sizeY);
    setMatrix(newMatrix, mat.data);
    return newMatrix;
}

int* getElement(matrix_t mat, size_t i, size_t j) {
    assert(i < mat.sizeY);
    assert(j < mat.sizeX);
    assert(mat.data);
    return mat.data+i*mat.sizeX+j;
}

long long det(const matrix_t mat) {
    assert(mat.data);
    assert(mat.sizeX == mat.sizeY);

    if (mat.sizeX == 1) return mat.data[0];
    if (mat.sizeX == 2) return  *getElement(mat, 0, 0)* *getElement(mat, 1, 1) -
                                *getElement(mat, 1, 0)* *getElement(mat, 0, 1);

    long long result = 0;
    matrix_t temp = createMatrix(mat.sizeX-1, mat.sizeY-1);

    for (size_t k = 0; k < mat.sizeX; k++) {
        if (*getElement(mat, 0, k) == 0) continue;
        for (size_t i = 1; i < mat.sizeY; i++) {
            for (size_t j = 0; j < k; j++) {
                *getElement(temp, i-1, j) = *getElement(mat, i, j);
            }
            for (size_t j = k+1; j < mat.sizeX; j++) {
                *getElement(temp, i-1, j-1) = *getElement(mat, i, j);
            }
        }
        long long complement = det(temp);
        result += ((k % 2 == 0) ? 1 : -1) * complement * *getElement(mat, 0, k);
    }
    delMatrix(&temp);
    return result;
}

void fillMatrix(matrix_t mat, const int filler) {
    assert(mat.data);

    for (size_t i = 0; i < mat.sizeX*mat.sizeY; i++)
        mat.data[i] = filler;

}

void setMatrix(matrix_t mat, const int* arr) {
    assert(mat.data);

    for (size_t i = 0; i < mat.sizeX*mat.sizeY; i++)
        mat.data[i] = arr[i];
}

void delMatrix(matrix* mat) {
    if (mat->data)
        free(mat->data);
}

void printMatrix(const matrix_t mat) {
    assert(mat.data);

    for (size_t i = 0; i < mat.sizeY; i++) {
        for (size_t j = 0; j < mat.sizeX; j++) {
            printf("%d ", mat.data[i*mat.sizeX+j]);
        }
        printf("\n");
    }

}


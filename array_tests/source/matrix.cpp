#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "matrix.h"

matrix_t createMatrix(size_t sizeX, size_t sizeY) {
    matrix_t newMatrix = {};
    newMatrix.data = (elementMatrix_t*) calloc(sizeX*sizeY, sizeof(elementMatrix_t));
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

    matrix_t result = createMatrix(mat1.sizeX, mat1.sizeY);

    for (size_t i = 0; i < mat1.sizeX*mat1.sizeY; i++)
        result.data[i] = mat1.data[i] + mat2.data[i];

    return result;
}

matrix_t multiplyMatrix(const matrix_t mat1, const matrix_t mat2) {
    assert(mat1.sizeX == mat2.sizeY);

    matrix_t result = createMatrix(mat2.sizeX, mat1.sizeY);

    for (size_t i = 0; i < result.sizeY; i++)
        for (size_t j = 0; j < result.sizeX; j++)
            for (size_t k = 0; k < mat1.sizeX; k++)
                *getElement(result, i, j) += *getElement(mat1, i, k) * *getElement(mat2, k, j);

    return result;
}

matrix_t copyMatrix(const matrix_t mat) {
    matrix_t newMatrix = createMatrix(mat.sizeX, mat.sizeY);
    setMatrix(newMatrix, mat.data);
    return newMatrix;
}

elementMatrix_t* getElement(matrix_t mat, size_t i, size_t j) {
    assert(i < mat.sizeY);
    assert(j < mat.sizeX);
    assert(mat.data);
    return mat.data+i*mat.sizeX+j;
}

elementMatrix_t det(const matrix_t mat) {
    assert(mat.data);
    assert(mat.sizeX == mat.sizeY);

    if (mat.sizeX == 1) return mat.data[0];
    if (mat.sizeX == 2) return  *getElement(mat, 0, 0)* *getElement(mat, 1, 1) -
                                *getElement(mat, 1, 0)* *getElement(mat, 0, 1);

    elementMatrix_t result = 0;
    matrix_t temp = createMatrix(mat.sizeX-1, mat.sizeY-1);
    //det(A) = sum(A[0][i]*complement(A[0][i] for i in range [0;sizeX-1])
    for (size_t k = 0; k < mat.sizeX; k++) {
        if (*getElement(mat, 0, k) == 0) //small, but very powerful optimisation
            continue;
        result += *getElement(mat, 0, k) * complement(mat, temp, 0, k);
    }
    delMatrix(&temp);
    return result;
}

elementMatrix_t complement(matrix_t mat, matrix_t temp, size_t y, size_t x) {
    assert(mat.sizeX == temp.sizeX + 1 && mat.sizeY == temp.sizeY + 1);
    assert(y < mat.sizeY);
    assert(x < mat.sizeX);

    //Copying to temporary array to calculate complementary of element of matrix
    //We have 4 blocks of data, so there are 4 for loops
    for (size_t i = 0; i < y; i++) {
        for (size_t j = 0; j < x; j++)
            *getElement(temp, i, j) = *getElement(mat, i, j);
        for (size_t j = x+1; j < mat.sizeX; j++)
            *getElement(temp, i, j-1) = *getElement(mat, i, j);
    }

    for (size_t i = y + 1; i < mat.sizeY; i++) {
        for (size_t j = 0; j < x; j++)
            *getElement(temp, i-1, j) = *getElement(mat, i, j);
        for (size_t j = x+1; j < mat.sizeX; j++)
            *getElement(temp, i-1, j-1) = *getElement(mat, i, j);
    }

    elementMatrix_t result = (((x+y) % 2 == 0) ? 1: -1) * det(temp);
    return result;
}

matrix_t transpose(const matrix_t mat) {
    if (!mat.data)
        return mat;
    matrix_t result = createMatrix(mat.sizeY, mat.sizeX);
    for (size_t i = 0; i < mat.sizeY; i++)
        for (size_t j = 0; j < mat.sizeX; j++)
            *getElement(result, j, i) = *getElement(mat, i, j);

    return result;
}

matrix_t inverse(const matrix_t mat) {
    matrix_t result = createMatrix(mat.sizeX, mat.sizeY);

    //creating temporary matrix, because we don't want to allocate memory on every complement() call
    matrix_t temp = createMatrix(mat.sizeX-1, mat.sizeY-1);
    for (size_t i = 0; i < mat.sizeY; i++)
        for (size_t j = 0; j < mat.sizeX; j++)
            *getElement(result, i, j) = complement(mat, temp, i, j);

    delMatrix(&temp);

    elementMatrix_t determinant = 0;
    //we already calculated all complementaries, so we don't want to do it again in det() function
    for (size_t i = 0; i < mat.sizeX; i++)
        determinant += *getElement(mat, 0, i) * *getElement(result, 0, i);

    printf("det = %lg\n", determinant);
    for (size_t i = 0; i < mat.sizeX*mat.sizeY; i++)
        result.data[i] /= determinant;

    matrix_t invertedMatrix = transpose(result);
    delMatrix(&result);
    return invertedMatrix;
}

void fillMatrix(matrix_t mat, const elementMatrix_t filler) {
    if (!mat.data)
        return;

    for (size_t i = 0; i < mat.sizeX*mat.sizeY; i++)
        mat.data[i] = filler;

}

void setMatrix(matrix_t mat, const elementMatrix_t* arr) {
    if (!mat.data)
        return;

    for (size_t i = 0; i < mat.sizeX*mat.sizeY; i++)
        mat.data[i] = arr[i];
}


void delMatrix(matrix* mat) {
    if (mat->data)
        free(mat->data);
    mat->data = NULL;
}

void printMatrix(const matrix_t mat) {
    assert(mat.data);

    for (size_t i = 0; i < mat.sizeY; i++) {
        for (size_t j = 0; j < mat.sizeX; j++) {
            printf("%lg ", mat.data[i*mat.sizeX+j]);
        }
        printf("\n");
    }

}


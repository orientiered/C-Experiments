#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"
#include "myVector.h"

const size_t MINIMUM_RESERVED = 5;

void* getElem(vector_t vec, size_t i) {
    assert(i < vec.size);
    return (char*)vec.base + i * vec.elemSize;
}

vector_t vectorCopyCtor(size_t size, size_t elemSize, const void* data) {
    vector_t newVector = vectorCtor(size, elemSize);
    memcpy(newVector.base, data, size*elemSize);
    return newVector;
}

void mergeSort(vector_t vec, int (*cmp)(const void* a, const void* b)) {
    if (vec.size <= 1) return;
    if (vec.size == 2) {
        if ((*cmp)(getElem(vec, 0), getElem(vec, 1)) == 1)
            swap(getElem(vec, 0), getElem(vec, 1), vec.elemSize);
        return;
    }

    //splitting array in two smaller
    vector_t base1 = vectorCopyCtor(vec.size/2, vec.elemSize, getElem(vec, 0));
    vector_t base2 = vectorCopyCtor(vec.size - vec.size/2, vec.elemSize, getElem(vec, vec.size/2));
    //sorting them
    mergeSort(base1, cmp);
    mergeSort(base2, cmp);
    //merging them
    mergeArrays(base1, base2, vec, cmp);
    //deleting temporary arrays
    vectorDtor(&base1);
    vectorDtor(&base2);
}

void mergeArrays(vector_t vec1, vector_t vec2, vector_t vec, int (*cmp)(const void* a, const void* b)) {
    assert(vec1.elemSize == vec2.elemSize);
    assert(vec1.elemSize == vec.elemSize);
    assert(vec.size >= vec1.size + vec2.size);

    size_t i = 0, j = 0;

    while(i < vec1.size && j < vec2.size) {
        int cmpResult = (*cmp)(getElem(vec1, i), getElem(vec2, j));
        if (cmpResult <= 0) {
            memcpy(getElem(vec, i+j), getElem(vec1, i), vec.elemSize);
            i++;
        } else {
            memcpy(getElem(vec, i+j), getElem(vec2, j), vec.elemSize);
            j++;
        }
    }

    if (i == vec1.size)
        memcpy(getElem(vec, i+j), getElem(vec2, j), (vec2.size-j)*vec.elemSize);
    else
        memcpy(getElem(vec, i+j), getElem(vec1, i), (vec1.size-i)*vec.elemSize);
}

void vectorDtor(vector_t* vec) {
    free(vec->base);
    vec->base = NULL;
}

vector_t vectorCtor(size_t size, size_t elemSize) {
    size_t reserved = (size < MINIMUM_RESERVED) ? MINIMUM_RESERVED : size;
    vector_t newVector = {NULL, size, reserved, elemSize};
    newVector.base = calloc(reserved, elemSize);
    return newVector;
}

vector_t vectorListCtor(size_t elemSize, ...) {

}

void* vectorPush(vector_t* vec, void* elem) {
    if (vec->size >= vec->reserved) {
        void *newBase = calloc(vec->reserved * 2, vec->elemSize);
        if (!newBase) return NULL;
        vec->reserved *= 2;
        memcpy(newBase, vec->base, vec->size*vec->elemSize);
        free(vec->base);
        vec->base = newBase;
    }
    vec->size++;
    memcpy(getElem(*vec, vec->size-1), elem, vec->elemSize);
    return getElem(*vec, vec->size-1);
}

void* vectorPop(vector_t* vec) {
    if (vec->size == 0) return NULL;
    vec->size--;
    return getElem(*vec, vec->size-1);
}

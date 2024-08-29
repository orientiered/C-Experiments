#ifndef MY_VECTOR_H
#define MY_VECTOR_H

typedef struct vector {
    void *base;
    size_t size;
    size_t elemSize;
} vector_t;

vector_t vectorCtor(size_t size, size_t elemSize);

vector_t vectorCopyCtor(size_t size, size_t elemSize, const void* data);

void vectorDtor(vector_t* vec);

void* getElem(vector_t vec, size_t i);

void mergeSort(vector_t vec, int (*cmp)(const void* a, const void* b));

void mergeArrays(vector_t vec1, vector_t vec2, vector_t vec, int (*cmp)(const void* a, const void* b));

#endif

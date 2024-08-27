#ifndef UTILS_H
#define UTILS_H

#define SWAP(a, b) do {swap(&(a), &(b), sizeof(a));}while(0)

void swap(void* a, void* b, size_t size);
void flushScanfBuffer();

#endif

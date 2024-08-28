#ifndef ARCHIVER_H
#define ARCHIVER_H

void encodeRLE(char *input, size_t size, FILE * out);

void decodeRLE(FILE *input, FILE *output);

#endif

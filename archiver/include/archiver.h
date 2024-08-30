#ifndef ARCHIVER_H
#define ARCHIVER_H

void encodeRLE(char *input, size_t size, FILE * out);

void encodeRLE_File(FILE *in, FILE *out);

void decodeRLE_File(FILE *input, FILE *output);

#endif

#include <stdio.h>
#include "archiver.h"

static void writeEncodedBlock(char **anchor, int *isSame, unsigned char *code, int *numSymbols) {
    fputc(code + (numSymbols), out);
    if (isSame == 1) {
        fputc(*anchor, out);
    } else (isSame == 0) {
        fwrite(anchor, 1, numSymbols, out);
    }
    *anchor += *numSymbols;
    *isSame = -1;
    *code = 0;
    *numSymbols = 0;
}

void encodeRLE(char *input, size_t size, FILE * out) {
    int numSymbols = 0;
    int isSame = -1;
    char *anchor = input;
    unsigned char code = 0;
    unsigned char mask = 1<<7;
    //10000000
    //first bit: 0  1
    //1 - equal symbols
    //0 - different symbols
    //other bits = number of symbols-1 (because 0 symbols doesn't make sense)
    for (size_t i = 0; i < size; i++) {
        if (numSymbols == 127) {
            writeEncodedBlock(&anchor, &isSame, &code, &numSymbols);
        } else
        if ((anchor - input) == i) {
            continue;
        }
        else if ((anchor - input) == (i-1)) {
            if (input[i-1] == input[i]) {
                isSame = 1;
                code |= mask;
            } else
                isSame = 0;
            numSymbols = 2;
        } else {
            if (((input[i] == input[i-1]) && (isSame == 1)) ||
                ((input[i] != input[i-1]) && (isSame == 0))) {
                numSymbols++;
            } else if ((input[i] == input[i-1]) && (isSame == 0)) {
                numSymbols--;
                writeEncodedBlock(&anchor, &isSame, &code, &numSymbols);
                i--;
            } else if (isSame == 1) {
                writeEncodedBlock(&anchor, &isSame, &code, &numSymbols);
            }
        }

    }
    if (anchor == (input + size-1)) {
        fputc(1, out);
        fputc(*anchor, out);
    } else {
        fputc(code + (numSymbols), out);
        if (code & mask)
            fputc(*anchor, out);
        else
            fwrite(anchor, 1, numSymbols, out);
    }
}

void decodeRLE(FILE *in, FILE *out) {
    unsigned char code = 0;
    unsigned char mask = 1<<7;
    int symbol = 0;
    while((symbol = fgetc(in)) != EOF) {
        if (code == 0) code = symbol;
        else if (code & mask) {
            for (int i = 0; i < (code - mask); i++)
                fputc(symbol, out);
            code = 0;
        } else {
            code--;
            fputc(symbol, out);
        }
    }
}

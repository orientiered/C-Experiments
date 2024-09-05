#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "archiver.h"

//when encoding, this text is the start of file
//when decoding, program will check if file is signed correctly
const char identifierText[] = "rlev.1.1\n";

static int bytesPerSymbol = 2;

/// @brief
/// @param anchor Start of the block
/// @param isSame Type of block
/// @param numSymbols Number of symbols in block
static void writeEncodedBlock(char **anchor, int *isSame, int *numSymbols, FILE *out);

static void writeEncodedBlock(char **anchor, int *isSame, int *numSymbols, FILE *out) {
    assert(*numSymbols <= 127);
    assert(*isSame != -1);

    const unsigned char firstBit = *isSame * (1 << 7); //128 if isSame = 1;
    //writing code to identify block
    fputc(firstBit + (*numSymbols), out);
    //writing block
    switch(*isSame) {
        case 0:
            fwrite(*anchor, bytesPerSymbol, *numSymbols, out);
            break;
        case 1:
            fwrite(*anchor, bytesPerSymbol, 1, out);
            break;
        default:
            break;
    }
    //moving anchor point and reseting other parameters
    *anchor += (*numSymbols * bytesPerSymbol);
    *isSame = -1;
    *numSymbols = 0;
}

/*!
    @brief Simple RLE encoder
    10000000 <br>
    first bit: 0 or 1 <br>
    1 - equal symbols <br>
    0 - different symbols <br>
    other bits = number of symbols
*/
void encodeRLE(char *input, size_t size, FILE * out) {
    int numSymbols = 0;
    int isSame = -1;
    char *anchor = input; //start of the current block
    const unsigned char maxSymbols = (1 << 7) - 1;

    //information to correctly decode -> size of symbol
    fputc(bytesPerSymbol, out);
    //archiver sign
    fwrite(identifierText, 1, sizeof(identifierText)-1, out);

    size_t i = 0;
    size_t limit = size - (size % bytesPerSymbol);
    for (; i < limit; i += bytesPerSymbol) {
        if (numSymbols == maxSymbols) {
            writeEncodedBlock(&anchor, &isSame, &numSymbols, out);
        } else if ((anchor - input) == i) {
            continue;
        } else if ((anchor - input) == (i-bytesPerSymbol)) {
            isSame = (memcmp(&input[i], &input[i-bytesPerSymbol], bytesPerSymbol) == 0) ? 1 : 0;
            //printf("isSame = %d\n", isSame);
            numSymbols = 2;
        } else {
            int cmpResult = (memcmp(&input[i], &input[i-bytesPerSymbol], bytesPerSymbol) == 0) ? 1 : 0;
            //printf("cmpResult = %d\n", cmpResult);
            if ((cmpResult && (isSame == 1)) ||
                (!cmpResult && (isSame == 0))) {
                numSymbols++;
                //printf("numSymbols = %d\n", numSymbols);
            } else if (cmpResult && (isSame == 0)) {
                numSymbols--;
                writeEncodedBlock(&anchor, &isSame, &numSymbols, out);
                i -= bytesPerSymbol;
            } else if (isSame == 1) {
                writeEncodedBlock(&anchor, &isSame, &numSymbols, out);
            }
        }
    }
    //putting last block to file
    if (isSame != -1)
        writeEncodedBlock(&anchor, &isSame, &numSymbols, out);
    //128 is unused value, because 0 same characters doesn't make sense
    fputc(128, out);
    for (i = anchor - input; i < size; i++)
        fputc(input[i], out);
}

void encodeRLE_File(FILE *in, FILE *out) {
    size_t inputSize = 0;
    fseek(in, 0, SEEK_END);
    inputSize = ftell(in);
    fseek(in, 0, SEEK_SET);
    char *inputString = (char *)calloc(inputSize, 1);
    fread(inputString, 1, inputSize, in);
    encodeRLE(inputString, inputSize, out);
    free(inputString);
}

void decodeRLE_File(FILE *in, FILE *out) {
    bytesPerSymbol = fgetc(in);
    if (bytesPerSymbol < 1 || bytesPerSymbol > 255) return;

    char fileSign[sizeof(identifierText)-1] = "";
    fread(fileSign, 1, sizeof(identifierText) - 1, in);

    if (strncmp(fileSign, identifierText, sizeof(identifierText) - 1) != 0) {
        printf("This file wasn't archived by RLE; can't decode\n");
        return;
    }

    int temp = 0;
    unsigned char code = 0;
    unsigned char mask = 1<<7;
    char *symbol = (char*) calloc(bytesPerSymbol, 1);
    while (1) {
        if (!code) {
            temp = fgetc(in);
            if (temp == EOF) break;
            //printf("code = %d + %d\n", temp / 128, temp % 128);
            code = (unsigned char) temp;
            continue;
        }

        if (code == 128) {
            while ((temp = fgetc(in)) != EOF)
                fputc((unsigned char) temp, out);

            break;
        }

        if (code & mask) {
            fread(symbol, bytesPerSymbol, 1, in);
            for (int k = 0; k < (code - mask); k++)
                fwrite(symbol, bytesPerSymbol, 1, out);
            code = 0;
        } else {
            while (code) {
                fread(symbol, bytesPerSymbol, 1, in);
                fwrite(symbol, bytesPerSymbol, 1, out);
                code--;
            }
        }
    }
    free(symbol);
}


void setBytesPerSymbol(size_t bytes) {
    if (bytes > 255) {
        printf("Too big symbol size. Symbol size must be <= 255\n");
        return;
    }
    bytesPerSymbol = bytes;
}

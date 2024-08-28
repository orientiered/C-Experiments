#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "archiver.h"

//when encoding, this text is the start of file
//when decoding, program will check if file is signed correctly
const char identifierText[] = "__rle__v.1.0\n";

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
            fwrite(*anchor, 1, *numSymbols, out);
            break;
        case 1:
            fputc(**anchor, out);
            break;
        default:
            break;
    }
    //moving anchor point and reseting other parameters
    *anchor += *numSymbols;
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
    const unsigned char maxSymbols = 1 << 7 - 1;

    //archiver sign
    fwrite(identifierText, 1, sizeof(identifierText), out);

    for (size_t i = 0; i < size; i++) {
        if (numSymbols == maxSymbols) {
            writeEncodedBlock(&anchor, &isSame, &numSymbols, out);
        } else if ((anchor - input) == i) {
            continue;
        } else if ((anchor - input) == (i-1)) {
            isSame = (input[i-1] == input[i]);
            numSymbols = 2;
        } else {
            if (((input[i] == input[i-1]) && (isSame == 1)) ||
                ((input[i] != input[i-1]) && (isSame == 0))) {
                numSymbols++;
            } else if ((input[i] == input[i-1]) && (isSame == 0)) {
                numSymbols--;
                writeEncodedBlock(&anchor, &isSame, &numSymbols, out);
                i--;
            } else if (isSame == 1) {
                writeEncodedBlock(&anchor, &isSame, &numSymbols, out);
            }
        }
    }

    //putting last block to file
    if (anchor == (input + size-1)) {
        //only one symbol
        fputc(1, out);
        fputc(*anchor, out);
    } else {
        writeEncodedBlock(&anchor, &isSame, &numSymbols, out);
    }
}


void decodeRLE(FILE *in, FILE *out) {
    char fileSign[sizeof(identifierText)] = "";
    fread(fileSign, 1, sizeof(identifierText) - 1, in);

    if (strcmp(fileSign, identifierText) != 0) {
        printf("This file wasn't archived by RLE; can't decode\n");
        return;
    }

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

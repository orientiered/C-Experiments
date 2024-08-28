#include <stdio.h>
#include <stdlib.h>
#include "archiver.h"

int main(int argc, char *argv[]) {
    if (argc != 4) return 0;
    else {
        FILE    *in  = fopen(argv[2], "rb"),
                *out = fopen(argv[3], "wb");

        size_t inputSize = 0;
        char *inputString = NULL;
        if (!in || !out) {
            printf("Can't open file\n");
            fclose(in);
            fclose(out);
            return 0;
        }
        switch(argv[1][0]) {
        case 'd':
            decodeRLE(in, out);
            break;
        case 'e':
            fseek(in, 0, SEEK_END);
            inputSize = ftell(in);
            fseek(in, 0, SEEK_SET);
            inputString = (char *)calloc(inputSize, 1);
            fread(inputString, 1, inputSize, in);
            encodeRLE(inputString, inputSize, out);
            free(inputString);
            break;
        default:
            printf("Bruh\n");
            break;
        }
        fclose(in);
        fclose(out);
    }

    return 0;
}

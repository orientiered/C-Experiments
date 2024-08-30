#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "archiver.h"
#include "argvProcessor.h"

int main(int argc, char *argv[]) {
    argVal_t flags[argsSize] = {};
    initFlags(flags);

    if (processArgs(flags, argc, argv) != GOOD_EXIT) {
        printf("Bad arguments\n");
        return 0;
    }
    const char *inputName = NULL;
    const char *outputName = NULL;
    if (flags[HELP].set) {
        printHelpMessage();
        return 0;
    }
    if (flags[INPUT].set) {
        inputName = flags[INPUT].val._string;
    } else {
        printf("No file to read\n");
        return 0;
    }
    if (flags[OUTPUT].set) {
        outputName = flags[OUTPUT].val._string;
    } else {
        printf("No file to write\n");
        return 0;
    }
    if (flags[ENCODE].set == flags[DECODE].set) {
        printf("Specify what you want to do\n");
    } else {
        FILE    *in  = fopen(inputName, "rb"),
                *out = fopen(outputName, "wb");

        if (flags[ENCODE].set) {
            encodeRLE_File(in, out);
        } else
        if (flags[DECODE].set) {
            decodeRLE_File(in, out);
        }

    }
    return 0;
//     if (argc != 4) return 0;
//     else {
//         FILE    *in  = fopen(argv[2], "rb"),
//                 *out = fopen(argv[3], "wb");
//
//         size_t inputSize = 0;
//         char *inputString = NULL;
//         if (!in || !out) {
//             printf("Can't open file\n");
//             fclose(in);
//             fclose(out);
//             return 0;
//         }
//         switch(argv[1][0]) {
//         case 'd':
//             decodeRLE(in, out);
//             break;
//         case 'e':
//             fseek(in, 0, SEEK_END);
//             inputSize = ftell(in);
//             fseek(in, 0, SEEK_SET);
//             inputString = (char *)calloc(inputSize, 1);
//             fread(inputString, 1, inputSize, in);
//             encodeRLE(inputString, inputSize, out);
//             free(inputString);
//             break;
//         default:
//             printf("Bruh\n");
//             break;
//         }
//         fclose(in);
//         fclose(out);
//     }

    return 0;
}

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

    if (flags[BYTES].set)
        setBytesPerSymbol(flags[BYTES].val._int);

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
}

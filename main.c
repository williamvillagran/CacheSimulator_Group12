#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[]){
    if (argc < 8){
        fprintf(stderr, "Usage: %s\n"
                        "-s <cache size - KB>       [ 8 to 8198 KB]\n"
                        "–b <block size>            [ 8 bytes to 64 bytes ]\n"
                        "–a <associativity>         [ 1, 2, 4, 8, 16 ]\n"
                        "–r <replacement policy>    [ RR ]\n"
                        "-u <percentage phys mem used> [ 0 to 100 ]\n"
                        "-n <Instr / Time Slice [ 0 to -1 ] -1 = max]\n"
                        "–f <trace file name> [ name of text file with the trace ]\n" ,argv[0]);
        return 1;
    }

    //Assign all CLI arguments to variables
    int cacheSize = atoi(argv[1]);
    int blockSize = atoi(argv[2]);
    int associativity  = atoi(argv[3]);
    int percentageMem = atoi(argv[5]);
    int intructionTimeSlice = atoi(argv[6]);

    char replacementPolicy[30];
    strncpy(replacementPolicy, argv[4], sizeof(replacementPolicy) - 1);
    replacementPolicy[sizeof(replacementPolicy) - 1] = '\0'; //Null-terminate
    

    char traceFile1[30];
    strncpy(traceFile1, argv[7], sizeof(traceFile1) - 1);
    traceFile1[sizeof(traceFile1) - 1] = '\0';  // Null-terminate

    
    char traceFile2[30];
    if (argv[8] != NULL) {
        //char traceFile2[30];
        strncpy(traceFile2, argv[8], sizeof(traceFile2) - 1);
        traceFile2[sizeof(traceFile2) - 1] = '\0';  // Null-terminate
    }

    char traceFile3[30];
    if (argv[9] != NULL) {
        //char traceFile3[30];
        strncpy(traceFile3, argv[9], sizeof(traceFile3) - 1);
        traceFile3[sizeof(traceFile3) - 1] = '\0';  // Null-terminate
    }





return 0;
}
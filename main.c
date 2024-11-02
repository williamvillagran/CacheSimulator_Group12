#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <main.h>

void inputOutput(int cache, int block, int associativity, char replacementPolicy[30], int percentageMem, int intructionTimeSlice,
                     char traceFile1[30], char traceFile2[30], char traceFile3[30]){
    printf("Cache Simulator - CS 3853 - Group 12\n\n");
    
    printf("Trace File(s):\n"
            "\t\t%s"
            "\t\t%s"
            "\t\t%s", traceFile1, traceFile2, traceFile3);

    printf("***** Cache Input Parameters *****");

    int cacheSize = calcCacheSize(1, 2, 3);
    printf("%d", "Cache Size:       %d", cacheSize);
    printf("%d", "Block Size:");
    printf("%d", "Associativity:");
    printf("%c", "Replacement Policy:");
    printf("%d", "Physical Memory:");
    printf("%d", "Percent Memory Used by System:");
    printf("%c", "Instructions/ Time Slice:");

}

void calculatedOutput(){
    int cacheSize = calcCacheSize(1, 2, 3);
    printf("***** Cache Calculated Values *****\n\n"
            "Total # Blocks:                \n"
            "Tag Size:                      \n"
            "Index Size:                    \n"
            "Total # Rows:                  \n"
            "Overhead Size:                 \n"
            "Implementation Memory Size:    \n"
            "Cost:                          \n");
}

void pmCalculatedOutput(){
    printf("**** Physical Memory Calculated Values *****");
    printf("Number of Physical Pages:");
    printf("Number of Pages for System:");
    printf("Size of Page Table Entry:");
    printf("Total RAM for Page Table(s):");
    
}





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

inputOutput(cacheSize, blockSize, associativity, replacementPolicy,
                percentageMem, intructionTimeSlice, traceFile1, traceFile2, traceFile3);




return 0;
}
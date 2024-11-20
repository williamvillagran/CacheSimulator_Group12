#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
 
int main(int argc, char *argv[]){
    
    
    if (argc < 0){
        fprintf(stderr, "Usage: %s\n"
                        "-s <cache size - KB>       [ 8 to 8198 KB]\n"
                        "–b <block size>            [ 8 bytes to 64 bytes ]\n"
                        "–a <associativity>         [ 1, 2, 4, 8, 16 ]\n"
                        "–r <replacement policy>    [ RR ]\n"
                        "–p <physical memory - MB> [ 1 MB to 4 GB ]\n"
                        "-u <percentage phys mem used> [ 0 to 100 ]\n"
                        "-n <Instr / Time Slice [ 0 to -1 ] -1 = max]\n"
                        "–f <trace file name> [ name of text file with the trace ]\n" ,argv[0]);
        return 1;
    }
    
    
    int cacheSize = 0;
    int blockSize = 0;
    int associativity  = 0;
    int physicalMem = 0;
    int percentageMem = 0;
    int instructionTimeSlice = 0;
    int fileCount = 0;
    int totalCacheAccess = 0;

    char replacementPolicy[30] = "";

    char traceFile1[250] = "";
    char traceFile2[250] = "";
    char traceFile3[250] = "";
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) 
        {
            cacheSize = atoi(argv[++i]);
        } 
        else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) 
        {
            blockSize = atoi(argv[++i]);
        } 
        else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) 
        {
            associativity = atoi(argv[++i]);
        } 
        else if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) 
        {
            strncpy(replacementPolicy, argv[++i], sizeof(replacementPolicy) - 1);
        } 
        else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) 
        {
            physicalMem = atoi(argv[++i]);
        } 
        else if (strcmp(argv[i], "-u") == 0 && i + 1 < argc) 
        {
            percentageMem = atoi(argv[++i]);
        } 
        else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) 
        {
            instructionTimeSlice = atoi(argv[++i]);
        } 
        
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) 
        {
            i++;
            
            if (traceFile1[0] == '\0') {
                strncpy(traceFile1, argv[i], sizeof(traceFile1) - 1);
                traceFile1[sizeof(traceFile1) - 1] = '\0';
            } 

            else if (traceFile2[0] == '\0') {
                strncpy(traceFile2, argv[i], sizeof(traceFile2) - 1);
                traceFile2[sizeof(traceFile2) - 1] = '\0';
            } 

            else if (traceFile3[0] == '\0') {
                strncpy(traceFile3, argv[i], sizeof(traceFile3) - 1);
                traceFile3[sizeof(traceFile3) - 1] = '\0';
            } 

            else {
                fprintf(stderr, "Error: Too many trace files. Only 3 allowed.\n");
                return 1;
            }
            fileCount++;
            //readFiles(traceFile1, traceFile2, traceFile3, totalCacheAccess);

        }

    }
    //Functions to print output (Milestone #1)
    inputOutput(cacheSize, blockSize, associativity, replacementPolicy, physicalMem, percentageMem, instructionTimeSlice, traceFile1, traceFile2, traceFile3);
    calculatedOutput(cacheSize, blockSize, associativity);
    pmCalculatedOutput(cacheSize, physicalMem, percentageMem, fileCount);



    
    readFiles(traceFile1, traceFile2, traceFile3, cacheSize, blockSize, associativity);












return 0;
}

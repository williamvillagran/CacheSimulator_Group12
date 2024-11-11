#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Calculations
int blockReturn(int cache, int block){
        return cache/block;
}
int tagReturn(int block){
        return log2(block);
}
int indexReturn(int numBlocks, int associativity){
        int numSets = numBlocks / associativity;
        return log2(numSets);
}
int numRows(int numBlocks, int associativity){
        return numBlocks / associativity;
}
int overheadSize(int numBlocks, int tagSize, int associativity) {
    int validBits = 1; 
    int dirtyBits = 1; 
    int overheadPerLine = tagSize + validBits + dirtyBits;
    return numBlocks * overheadPerLine;
}
double cost(int cacheSize, int blockSize, int overhead) {
    double costPerByte = 0.05;  // Was confused here we can adjust if needed
    return (cacheSize + overhead) * costPerByte;
}
int numPhysPages(int physicalMem, int pageSize) {
    return physicalMem / pageSize;
}
int numPagesSys(int physicalMem, int percentageMem, int pageSize) {
    int sysMem = (physicalMem * percentageMem) / 100;
    return sysMem / pageSize;
}
int sizePTE() {
    return 4; 
}

int totalRAMPT(int numPages, int sizePTE) {
    return numPages * sizePTE;
}



//Console Outputs
void inputOutput(int cache, int block, int associativity, char replacementPolicy[],
                         int physicalMem, int percentageMem, int intructionTimeSlice,
                         char traceFile1[], char traceFile2[], char traceFile3[]){
    printf("Cache Simulator - CS 3853 - Group 12\n\n");
    
    printf("Trace File(s):\n"
            "\t\t%s\n"
            "\t\t%s\n"
            "\t\t%s\n", traceFile1, traceFile2, traceFile3);


    printf("***** Cache Input Parameters *****\n\n"
            "Cache Size:                    %d\n"
            "Block Size:                    %d\n"
            "Associativity:                 %d\n"
            "Replacement Policy:            %s\n"
            "Physical Memory:               %d\n"
            "Percent Memory Used by System: %d\n"
            "Instructions / Time Slice:     %d\n"
            ,cache, block, associativity, replacementPolicy, physicalMem, percentageMem, intructionTimeSlice);

}

void calculatedOutput(int cache, int block, int associativity){
    printf("***** Cache Calculated Values *****\n\n"
            "Total # Blocks:                \n"
            "Tag Size:                      \n"
            "Index Size:                    \n"
            "Total # Rows:                  \n"
            "Overhead Size:                 \n"
            "Implementation Memory Size:    \n"
            "Cost:                          \n"
            ,blockReturn(cache, block), tagReturn(block), indexReturn(blockReturn(cache, block), associativity),
                numRows(blockReturn(cache, block), associativity), NULL, NULL, NULL);
}               //Replace NULL with actual values

void pmCalculatedOutput(){
    printf("***** Physical Memory Calculated Values *****\n\n"
            "Number of Physical Pages:      \n"
            "Number of Pages for System:    \n"
            "Size of Page Table Entry:      \n"
            "Total RAM for Page Table(s):   \n"
            , NULL, NULL, NULL, NULL);
            //Replace NULL for actual values
}

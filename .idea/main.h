#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Calculations
int blockReturn(int cache, int block){
        int convertedCache = cache * 1024;
        return convertedCache/block;
}
int tagReturn(int sizeBlock, int numBlock, int associativity){
        int result;
        int bit32 = 32;
        int offset = log2(sizeBlock);

        result = bit32 - offset;
        
        int index = numBlock/associativity;
        index = log2(index);

        result = result - index;
        
        return result;
}
int indexReturn(int numBlocks, int associativity){
        int numSets = numBlocks / associativity;
        return log2(numSets);
}
int numRows(int numBlocks, int associativity){
        return numBlocks / associativity;
}
int overheadSize(int numBlocks, int tagSize) {

    int ret = (tagSize + 1) / 8;

    ret = ret * numBlocks;

    return ret;
    //return numBlocks * tagSize / 8;
}
double cost(int implementationMemorySize) {
    double memorySizeKB = implementationMemorySize / 1024.0;
    return memorySizeKB * 0.15;
}
int numPhysPages(int physicalMem) {
    int pageSize = 4096; // 4 KB
    return (physicalMem * 1024 * 1024) / pageSize; // convert MB to bytes
}
int numPagesSys(int physMem, int percentageMem) {
    float r = (float)percentageMem / 100.00;
    int systemMemKB = physMem * r * 1024; 
    int numPages = systemMemKB / 4;  

    return numPages;  
}

int sizePTE() {
    return 19; // 19 bits per page table entry
}
int totalRAMPT(int cache, int numPTEs, int sizePTE, int flagCount) {
    return (cache * 1024) * flagCount * sizePTE / 8;
}


//Console Outputs
void inputOutput(int cache, int block, int associativity, char replacementPolicy[],
                         int physicalMem, float percentageMem, int intructionTimeSlice,
                         char traceFile1[], char traceFile2[], char traceFile3[]){
    printf("Cache Simulator - CS 3853 - Group 12\n\n");
    
    printf("Trace File(s):\n"
            "\t\t%s\n"
            "\t\t%s\n"
            "\t\t%s\n", traceFile1, traceFile2, traceFile3); //


    printf("***** Cache Input Parameters *****\n\n"
            "Cache Size:                    %d KB\n"
            "Block Size:                    %d bytes\n"
            "Associativity:                 %d\n"
            "Replacement Policy:            %s\n"
            "Physical Memory:               %d\n"
            "Percent Memory Used by System: %.1lf%%\n"
            "Instructions / Time Slice:     %d\n"
            ,cache, block, associativity, replacementPolicy, physicalMem, percentageMem, intructionTimeSlice);

}
void calculatedOutput(int cache, int block, int associativity) {
    int numBlocks = blockReturn(cache, block);
    int tagSize = tagReturn(block, blockReturn(cache, block), associativity);
    int indexSize = indexReturn(numBlocks, associativity);
    int totalRows = numRows(numBlocks, associativity);
    int overhead = overheadSize(numBlocks, tagSize);
    int implementationMemSize = (numBlocks * block) + overhead;
    double cacheCost = cost(implementationMemSize);

    printf("\n***** Cache Calculated Values *****\n\n"
           "Total # Blocks:                %d\n"
           "Tag Size:                      %d bits\n" 
           "Index Size:                    %d bits\n" 
           "Total # Rows:                  %d\n"
           "Overhead Size:                 %d\n"
           "Implementation Memory Size:    %d KB(%d bytes)\n" 
           "Cost:                          $%.2lf @ $%.2lf per KB\n",
           numBlocks, tagSize, indexSize, totalRows, overhead, implementationMemSize/1024, implementationMemSize, cacheCost, (cacheCost / (implementationMemSize/1024)));
}
void pmCalculatedOutput(int cache, int physicalMem, int percentageMem, int flagCount) {
    int totalPhysPages = numPhysPages(physicalMem);
    int systemPages = numPagesSys(physicalMem, percentageMem);
    int sizePTEBits = sizePTE();
    int totalRAMForPT = totalRAMPT(cache, totalPhysPages, sizePTEBits, flagCount);


    printf("\n***** Physical Memory Calculated Values *****\n\n"
           "Number of Physical Pages:      %d\n"
           "Number of Pages for System:    %d\n"
           "Size of Page Table Entry:      %d bits\n" 
           "Total RAM for Page Table(s):   %d bytes\n", //
           totalPhysPages, systemPages, sizePTEBits, totalRAMForPT);
}
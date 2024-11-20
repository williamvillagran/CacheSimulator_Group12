#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/****************************************************************************/
// Cache structures
typedef struct {
    unsigned int tag;  
    int valid;        
    int metadata;      
} CacheBlock;

typedef struct {
    CacheBlock *blocks;
} CacheSet;

typedef struct {
    CacheSet *sets;
    int numSets;       
    int associativity; 
    int blockSize;     
} Cache;

Cache initializeCache(int cacheSize, int blockSize, int associativity) {
    Cache cache;
    int numBlocks = (cacheSize * 1024) / blockSize;
    cache.numSets = numBlocks / associativity;
    cache.associativity = associativity;
    cache.blockSize = blockSize;
    cache.sets = malloc(sizeof(CacheSet) * cache.numSets);

    for (int i = 0; i < cache.numSets; i++) {
        cache.sets[i].blocks = malloc(sizeof(CacheBlock) * associativity);
        for (int j = 0; j < associativity; j++) {
            cache.sets[i].blocks[j].valid = 0;
            cache.sets[i].blocks[j].metadata = 0;
        }
    }
    return cache;
}

int accessCache(Cache *cache, unsigned int address, int *hits, int *misses, int *compMisses) {
    int index = (address / cache->blockSize) % cache->numSets;
    unsigned int tag = address / (cache->blockSize * cache->numSets);
    CacheSet *set = &cache->sets[index];

    // if (!accessedBlocks[tag]) {
    //     (*compMisses)++;      // Increment compulsory miss count
    //     accessedBlocks[tag] = true; // Mark the block as accessed
    // }

    for (int i = 0; i < cache->associativity; i++) {
        if (set->blocks[i].valid && set->blocks[i].tag == tag) {
            (*hits)++;
            return 1; // Cache hit
        }
    }

    // Cache miss: Replace a block (e.g., round-robin)
    (*misses)++;
    int replaceIndex = rand() % cache->associativity; // Random replacement
    set->blocks[replaceIndex].tag = tag;
    set->blocks[replaceIndex].valid = 1;
    return 0; // Cache miss
}

void freeCache(Cache *cache) {
    for (int i = 0; i < cache->numSets; i++) {
        free(cache->sets[i].blocks);
    }
    free(cache->sets);
}

double calculateHitRate(int hits, int totalAccesses) {
    return (double)hits / totalAccesses * 100.0;
}

double calculateMissRate(int misses, int totalAccesses) {
    return (double)misses / totalAccesses * 100.0;
}

double calculateCPI(int totalCycles, int instructions) {
    return (double)totalCycles / instructions;
}

/// 
///  
int calculateCompMisses(int cacheSize, int blockSize) {

}



/*************************************************************************/

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

// Milestone 2 outputs *****************************************************

void cacheSimResult(int totalAccesses, int totalInst, int totalDstBytes, int totalSrcBytes, int hits, int misses, int compMisses, int confMisses){
    float srcDstBytes = (float) totalSrcBytes + totalDstBytes;
    
    printf("\n***** CACHE SIMULATION RESULTS *****\n\n"
            "Total Cache Accesses:          %d\n"
            "Instruction Bytes:             %d "
            " SrcDst Bytes:                  %.2f\n"
            "Cache Hits:                    %d\n"
            "Cache Misses:                  %d\n"
            "--- Compulsory Misses:         %d\n"
            "--- Conflict Misses:           %d\n"
            , totalAccesses, totalInst, srcDstBytes, hits, misses, compMisses, confMisses);
}

void cacheHitMiss(float cacheHits, float missRate, float cpi, int uSpace, int uBlocks){
    printf("\n***** ***** CACHE HIT & MISS RATE: ***** *****\n\n"
            "Hit Rate:                      %.4f%%\n"
            "Miss Rate:                     %.4f%%\n"
            "CPI:                           %.2f Cycles/Instruction\n"
            "Unused Cache Space:            %d\n"
            "Unused Cache Blocks:           %d\n"
            , cacheHits, missRate, cpi, uSpace, uBlocks);
}

void readFiles(char *traceFile1, char *traceFile2, char *traceFile3, int cacheSize, int blockSize, int associativity) {
    char buffer[256];
    int hits = 0;
    int misses = 0;
    int compMisses = 0;
    int confMisses = 0;
    int totalCycles = 0;
    int totalAccesses = 0;
    int totalInst = 0;
    int totalDst = 0;
    int totalSrc = 0;

    Cache cache = initializeCache(cacheSize, blockSize, associativity);
    FILE *files[] = {fopen(traceFile1, "r"), fopen(traceFile2, "r"), fopen(traceFile3, "r")};
    for (int f = 0; f < 3; f++) {
        if (files[f] == NULL) continue;

        while (fgets(buffer, sizeof(buffer), files[f])) {
            unsigned int address;
            int bitMulti;

            if (strncmp(buffer, "EIP", 3) == 0) {
                sscanf(buffer, "EIP (%d): %x", &bitMulti, &address);
                totalInst += bitMulti;
                totalCycles += accessCache(&cache, address, &hits, &misses, &compMisses) ? 1 : 4;
                totalCycles += 2; // Instruction execution
            } else if (strncmp(buffer, "dstM", 4) == 0 || strncmp(buffer, "srcM", 4) == 0) {
                unsigned int dst, src;
                sscanf(buffer, "dstM: %x srcM: %x", &dst, &src);
                if (dst != 0) {
                    totalDst++;
                    totalCycles += accessCache(&cache, dst, &hits, &misses, &compMisses) ? 1 : 4;
                    totalCycles += 1;
                }
                if (src != 0) {
                    totalSrc++;
                    totalCycles += accessCache(&cache, src, &hits, &misses, &compMisses) ? 1 : 4;
                    totalCycles += 1;
                }
            }
        }
        fclose(files[f]);
    }

    totalAccesses = hits + misses;

    int totalDstBytes = totalDst * 4;
    int totalSrcBytes = totalSrc * 4;

    double hitRate = calculateHitRate(hits, totalAccesses);
    double missRate = calculateMissRate(misses, totalAccesses);
    double cpi = calculateCPI(totalCycles, totalAccesses);

    
    cacheSimResult(totalAccesses, totalInst, totalDstBytes, totalSrcBytes, hits, misses, compMisses, confMisses);
    cacheHitMiss(hitRate, missRate, cpi, 0, 0);
    //Replace 0's with actual values


    
    //printf("Cache Hits: %d, Misses: %d, Hit Rate: %.2f%%, Miss Rate: %.2f%%, CPI: %.2f\n",
    //    hits, misses, hitRate, missRate, cpi);

    freeCache(&cache);
}

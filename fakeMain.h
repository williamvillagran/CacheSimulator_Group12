#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Cache structures
typedef struct {
    unsigned int tag;  // Tag for the block
    int valid;         // Valid bit
    int metadata;      // For replacement policy (e.g., round-robin counter)
} CacheBlock;

typedef struct {
    CacheBlock *blocks; // Blocks in the set
} CacheSet;

typedef struct {
    CacheSet *sets;    // Array of cache sets
    int numSets;       // Number of sets
    int associativity; // Associativity level
    int blockSize;     // Block size
} Cache;

// Cache functions
Cache initializeCache(int cacheSize, int blockSize, int associativity);
int accessCache(Cache *cache, unsigned int address, int *hits, int *misses);
void freeCache(Cache *cache);

// Metric calculations
double calculateHitRate(int hits, int totalAccesses);
double calculateMissRate(int misses, int totalAccesses);
double calculateCPI(int totalCycles, int instructions);

// File processing
void readFiles(char *traceFile1, char *traceFile2, char *traceFile3, int cacheSize, int blockSize, int associativity);

#endif

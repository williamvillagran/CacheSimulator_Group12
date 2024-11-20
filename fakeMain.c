#include "fakeMain.h"

int main(int argc, char *argv[]) {
    if (argc < 9) {
        fprintf(stderr, "Usage: %s\n"
                        "-s <cache size in KB> [8 to 8192 KB]\n"
                        "-b <block size> [8 to 64 bytes]\n"
                        "-a <associativity> [1, 2, 4, 8, 16]\n"
                        "-f <trace file 1> [-f <trace file 2>] [-f <trace file 3>]\n", argv[0]);
        return 1;
    }

    int cacheSize = 0;
    int blockSize = 0;
    int associativity = 0;
    char traceFile1[250] = "", traceFile2[250] = "", traceFile3[250] = "";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            cacheSize = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            blockSize = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            associativity = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            if (traceFile1[0] == '\0') {
                strncpy(traceFile1, argv[++i], sizeof(traceFile1) - 1);
            } else if (traceFile2[0] == '\0') {
                strncpy(traceFile2, argv[++i], sizeof(traceFile2) - 1);
            } else if (traceFile3[0] == '\0') {
                strncpy(traceFile3, argv[++i], sizeof(traceFile3) - 1);
            } else {
                fprintf(stderr, "Too many trace files. Only 3 are allowed.\n");
                return 1;
            }
        }
    }

    // Validate inputs
    if (cacheSize < 8 || cacheSize > 8192 || blockSize < 8 || blockSize > 64 || 
        (associativity != 1 && associativity != 2 && associativity != 4 && associativity != 8 && associativity != 16)) {
        fprintf(stderr, "Invalid cache configuration.\n");
        return 1;
    }

    // Process trace files
    readFiles(traceFile1, traceFile2, traceFile3, cacheSize, blockSize, associativity);

    return 0;
}

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

int accessCache(Cache *cache, unsigned int address, int *hits, int *misses) {
    int index = (address / cache->blockSize) % cache->numSets;
    unsigned int tag = address / (cache->blockSize * cache->numSets);
    CacheSet *set = &cache->sets[index];

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

void readFiles(char *traceFile1, char *traceFile2, char *traceFile3, int cacheSize, int blockSize, int associativity) {
    char buffer[256];
    int hits = 0, misses = 0, totalCycles = 0, totalAccesses = 0;

    Cache cache = initializeCache(cacheSize, blockSize, associativity);
    FILE *files[] = {fopen(traceFile1, "r"), fopen(traceFile2, "r"), fopen(traceFile3, "r")};
    for (int f = 0; f < 3; f++) {
        if (files[f] == NULL) continue;

        while (fgets(buffer, sizeof(buffer), files[f])) {
            unsigned int address;

            if (strncmp(buffer, "EIP", 3) == 0) {
                sscanf(buffer, "EIP (%*d): %x", &address);
                totalAccesses++;
                totalCycles += accessCache(&cache, address, &hits, &misses) ? 1 : 4;
                totalCycles += 2; // Instruction execution
            } else if (strncmp(buffer, "dstM", 4) == 0 || strncmp(buffer, "srcM", 4) == 0) {
                unsigned int dst, src;
                sscanf(buffer, "dstM: %x srcM: %x", &dst, &src);
                if (dst != 0) {
                    totalAccesses++;
                    totalCycles += accessCache(&cache, dst, &hits, &misses) ? 1 : 4;
                    totalCycles += 1;
                }
                if (src != 0) {
                    totalAccesses++;
                    totalCycles += accessCache(&cache, src, &hits, &misses) ? 1 : 4;
                    totalCycles += 1;
                }
            }
        }
        fclose(files[f]);
    }

    double hitRate = calculateHitRate(hits, totalAccesses);
    double missRate = calculateMissRate(misses, totalAccesses);
    double cpi = calculateCPI(totalCycles, totalAccesses);

    printf("Cache Hits: %d, Misses: %d, Hit Rate: %.2f%%, Miss Rate: %.2f%%, CPI: %.2f\n",
           hits, misses, hitRate, missRate, cpi);

    freeCache(&cache);
}

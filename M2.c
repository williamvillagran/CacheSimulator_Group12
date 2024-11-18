// /************************************************************
//  * 
//  * Attempt to read the file. Seeing a Segmentation Fault when reading a single file.
//  * 
// *************************************************************/


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
// #include "main.h"

// bool accessedBlocks[256] = {false};

// void simCacheAccess(int indexReturn, int blockReturn, int associativity, unsigned int address, int tagReturn, int *hits, int *misses, int *compMisses, int *conflictMisses) {
//     int index = indexReturn;
//     int tag = tagReturn;
    
//     // Cache Hit
//     for (int i = 0; i < associativity; i++) {
//         if (indexReturn && tagReturn == index && tag) {
//             hits++;
//             return; 
//         }
//     }

//     // Misses
//     (*misses)++;

//     // Compulsory Miss
//     if (!accessedBlocks[index]) {
//         (*compMisses)++;
//         accessedBlocks[index] = true; // Mark this block as accessed
//     } 
//     else 
//     {
//         (*conflictMisses)++;
//     }
// }

// int main(int argc, char *argv[]){

//     char buffer[256];
//     char filePath1[1024]; // Use a larger buffer for safety
//     char filePath2[1024]; // Use a larger buffer for safety
//     char filePath3[1024]; // Use a larger buffer for safety

//     snprintf(filePath1, sizeof(filePath1), "./Traces4Debugging/%s", argv[1]);
//     snprintf(filePath2, sizeof(filePath2), "./Traces4Debugging/%s", argv[2]);
//     snprintf(filePath3, sizeof(filePath3), "./Traces4Debugging/%s", argv[3]);

//     FILE *file1 = fopen(filePath1, "r");
//     FILE *file2 = fopen(filePath2, "r");
//     FILE *file3 = fopen(filePath3, "r");

//     // M2 output metrics
//     int totalCacheAccess = 0;
//     int hits = 0;
//     int misses = 0;
//     int compMisses = 0;
//     int conflictMisses = 0;
//     int totalCacheAccess = 0;

//     // Read from file1
//     while (fgets(buffer, sizeof(buffer), file1) > 0) {
//         // get instruction address
//         if (strncmp(buffer, "EIP", 3) == 0) {
//             unsigned int address;
//             sscanf(buffer, "EIP (%*d): %x", &address);
//             totalCacheAccess++;
//             printf("File1 Instruction Address: %x\n", address);            
//         }
//         // get destination and source address
//         else if (strncmp(buffer, "dstM", 4) == 0 || strncmp(buffer, "srcM", 4) == 0) {
//             unsigned int dst;
//             unsigned int src;
//             sscanf(buffer, "dstM: %x srcM: %x", &dst, &src);
//             if (dst != 0) {
//                 totalCacheAccess++;
//                 printf("File1 Destination Address: %x\n", dst);
//             }

//             if (src != 0) {
//                 totalCacheAccess++;
//                 printf("File1 Source Address: %x\n", src);
//             }

//         }
//     }

//     // Read from file2
//     while (fgets(buffer, sizeof(buffer), file2) > 0) {
//         // get instruction address
//         if (strncmp(buffer, "EIP", 3) == 0) {
//             unsigned int address;
//             sscanf(buffer, "EIP (%*d): %x", &address);
//             totalCacheAccess++;
//             printf("File2 Instruction Address: %x\n", address);
//         }
//         // get destination and source address
//         else if (strncmp(buffer, "dstM", 4) == 0 || strncmp(buffer, "srcM", 4) == 0) {
//             unsigned int dst;
//             unsigned int src;
//             sscanf(buffer, "dstM: %x srcM: %x", &dst, &src);
//             if (dst != 0) {
//                 totalCacheAccess++;
//                 printf("File2 Destination Address: %x\n", dst);
//             }
//             if (src != 0) {
//                 totalCacheAccess++;
//                 printf("File2 Source Address: %x\n", src);
//             }
//         }
//     }

//     // Read from file3
//     while (fgets(buffer, sizeof(buffer), file3) > 0) {
//         // get instruction address
//         if (strncmp(buffer, "EIP", 3) == 0) {
//             unsigned int address;
//             sscanf(buffer, "EIP (%*d): %x", &address);
//             totalCacheAccess++;
//             printf("File1 Instruction Address: %x\n", address);
//         }
//         // get destination and source address
//         else if (strncmp(buffer, "dstM", 4) == 0 || strncmp(buffer, "srcM", 4) == 0) {
//             unsigned int dst;
//             unsigned int src;
//             sscanf(buffer, "dstM: %x srcM: %x", &dst, &src);
//             if (dst != 0) {
//                 totalCacheAccess++;
//                 printf("File1 Destination Address: %x\n", dst);
//             }
//             if (src != 0) {
//                 totalCacheAccess++;
//                 printf("File1 Source Address: %x\n", src);
//             }
//         }
//     }

//     // Close the files
//     fclose(file1);
//     fclose(file2);
//     fclose(file3);

//     printf("Total Cache Accesses: %d\n", totalCacheAccess);


//     return EXIT_SUCCESS;
// }
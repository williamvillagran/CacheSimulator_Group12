/************************************************************
 * 
 * Attempt to read the file. Seeing a Segmentation Fault when reading a single file.
 * 
*************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){


    char buffer[256];
    char filePath1[32000]; // Use a larger buffer for safety
    char filePath2[4096]; // Use a larger buffer for safety
    char filePath3[4096]; // Use a larger buffer for safety

    FILE *file1;
    FILE *file2;
    FILE *file3;

    snprintf(filePath1, sizeof(filePath1), "./Traces4Debugging/%s", argv[1]);
    snprintf(filePath2, sizeof(filePath2), "./Traces4Debugging/%s", argv[2]);
    snprintf(filePath3, sizeof(filePath3), "./Traces4Debugging/%s", argv[3]);



    file1 = fopen(filePath1, "r");
    file2 = fopen(filePath2, "r");
    file3 = fopen(filePath3, "r"); 

    // Read from file1
    while (fread(buffer, 1, sizeof(buffer) - 1, file1) > 0) {
        buffer[sizeof(buffer) - 1] = '\0';
        printf("File1: %s", buffer);
    }

    // Read from file2
    while (fread(buffer, 1, sizeof(buffer) - 1, file2) > 0) {
        buffer[sizeof(buffer) - 1] = '\0';
        printf("File2: %s", buffer);
    }

    // Read from file3
    while (fread(buffer, 1, sizeof(buffer) - 1, file3) > 0) {
        buffer[sizeof(buffer) - 1] = '\0';
        printf("File3: %s", buffer);
    }

    // Close the files
    fclose(file1);
    fclose(file2);
    fclose(file3);




    return EXIT_SUCCESS;
}
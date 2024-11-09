#include <math.h>


void inputOutput(){
    printf("Cache Simulator - CS 3853 - Group 12\n\n");
    
    printf("Trace File(s):\n"
            "\t\t%s\n"
            "\t\t%s\n"
            "\t\t%s\n", NULL, NULL, NULL);

    printf("***** Cache Input Parameters *****\n\n"
            "Cache Size:                    %d\n"
            "Block Size:                    %d\n"
            "Associativity:                 %d\n"
            "Replacement Policy:            %s\n"
            "Physical Memory: 1024          %d\n"
            "Percent Memory Used by System: %d\n"
            "Instructions / Time Slice:     %d\n");

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
    printf("***** Physical Memory Calculated Values *****\n\n"
            "Number of Physical Pages:      \n"
            "Number of Pages for System:    \n"
            "Size of Page Table Entry:      \n"
            "Total RAM for Page Table(s):   \n");
}
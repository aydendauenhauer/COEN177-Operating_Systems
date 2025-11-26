//Name: Ayden Dauenhauer
//Date: Mar 3, 2025
//Title: Lab8 - Memory Management
//Description: To simulate three basic page replacement algorithms and evaluate the
//             comparative performance of these algorithms with different cache sizes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int pageno;
    // Any other useful values associated with the page, e.g. referenced
} ref_page;

int main(int argc, char *argv[]){
    int cacheSize = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[cacheSize]; // Virtual cache for simulator
    char inputBuffer[100]; // Buffer to hold input from test file
    int totalFaults = 0; // Keeps track of the total page faults

    int i;
    for (i = 0; i < cacheSize; i++){ // Initialize cache array
        cache[i].pageno = -1;
    }

    int placeInArray = 0;
    while (fgets(inputBuffer, 100, stdin)){
        int page_num = atoi(inputBuffer); // Stores number read from file as an int

        bool foundInCache = false;
        for(i=0; i<cacheSize; i++){
            if(cache[i].pageno == page_num){
                foundInCache = true;
                break; // Break out of loop because found page_num in cache
            }
        }
        if(foundInCache == false){
            printf("%d\n", page_num);
            cache[placeInArray].pageno = page_num;
            totalFaults++;
            placeInArray = (placeInArray + 1) % cacheSize;
        }
    }

    return 0;
}
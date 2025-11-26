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
    int lastUsed;
} ref_page;

int main(int argc, char *argv[]){
    int cacheSize = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[cacheSize]; // Virtual cache for simulator
    char inputBuffer[100]; // Buffer to hold input from test file
    int totalFaults = 0; // Keeps track of the total page faults
    int counter = 0; // Counter that increments each time a new page request is made

    int i;
    for (i = 0; i < cacheSize; i++){ // Initialize cache array
        cache[i].pageno = -1;
        cache[i].lastUsed = 0;
    }

    while (fgets(inputBuffer, 100, stdin)){
        int page_num = atoi(inputBuffer); // Stores number read from file as an int
        counter++;

        bool foundInCache = false;
        for(i=0; i<cacheSize; i++){
            if(cache[i].pageno == page_num){
                foundInCache = true;
                cache[i].lastUsed = counter;
                break; // Break out of loop because found page_num in cache
            }
        }
        if(foundInCache == false){
            printf("%d\n", page_num);

            // Try to find an empty slot first
            int empty_index = -1;
            for(i = 0; i < cacheSize; i++){
                if(cache[i].pageno == -1){
                    empty_index = i;
                    break;
                }
            }
            // If no empty slot, select the least recently used page
            if(empty_index == -1){
                int lru_index = 0;
                for(i = 1; i < cacheSize; i++){
                    if(cache[i].lastUsed < cache[lru_index].lastUsed)
                        lru_index = i;
                }
                empty_index = lru_index;
            }

            cache[empty_index].pageno = page_num;
            cache[empty_index].lastUsed = counter;
            totalFaults++;
        }
    }

    return 0;
}
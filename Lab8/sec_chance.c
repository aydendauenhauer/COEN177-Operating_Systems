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
    int ref;
} ref_page;

int main(int argc, char *argv[]){
    int cacheSize = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[cacheSize]; // Virtual cache for simulator
    char inputBuffer[100]; // Buffer to hold input from test file
    int totalFaults = 0; // Keeps track of the total page faults
    int pointer = 0; // Points to the candidate for replacement

    int i;
    for (i = 0; i < cacheSize; i++){ // Initialize cache array
        cache[i].pageno = -1;
        cache[i].ref = 0;
    }

    while (fgets(inputBuffer, 100, stdin)){
        int page_num = atoi(inputBuffer); // Stores number read from file as an int

        bool foundInCache = false;
        for(i=0; i<cacheSize; i++){
            if(cache[i].pageno == page_num){
                foundInCache = true;
                cache[i].ref = 1;
                break; // Break out of loop because found page_num in cache
            }
        }
        if(foundInCache == false){
            printf("%d\n", page_num);

            while(cache[pointer].ref == 1){
                cache[pointer].ref = 0;
                pointer = (pointer + 1) % cacheSize;
            }

            cache[pointer].pageno = page_num;
            cache[pointer].ref = 1;
            pointer = (pointer + 1) % cacheSize;
            totalFaults++;
        }
    }

    return 0;
}
//Name: Ayden Dauenhauer
//Date: Mar 3, 2025
//Title: Lab8 - Memory Management
//Description: To simulate three basic page replacement algorithms and evaluate the
//             comparative performance of these algorithms with different cache sizes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer [sizeof(int)];
    int i;

    int numRequests = 50;
    int possiblePages = 25;

    fp = fopen("testInput.txt", "w");
    for (i=0; i<numRequests; i++){ //Use a number you can test by hand, >possiblePages to force cache hits
        sprintf(buffer, "%d\n", rand()%possiblePages); //Small for hand testing, >cacheSize to force cache miss
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}
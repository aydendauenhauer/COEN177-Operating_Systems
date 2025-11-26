//Name: Ayden Dauenhauer
//Date: Mar 10, 2025
//Title: Lab9 - File Performance Measurement
//Description: To evaluate file system performance in the face of sequential I/O requests,
//             mainly disk reads and writes and to evaluate the impact of multiple
//             competing threads attempting to read/write simultaneously

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int buffer_size = atoi(argv[2]);
    char *buffer = malloc(buffer_size);
    FILE *fp;
    fp = fopen(argv[1], "rb");
    FILE *out;
    out = fopen("copy.out", "wb");

    int n;
    while ((n = fread(buffer, 1, buffer_size, fp)) > 0) {
        fwrite(buffer, 1, n, out);
    }
    fclose(fp);

    return 0;
}
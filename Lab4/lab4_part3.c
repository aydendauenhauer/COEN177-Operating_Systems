//Name: Ayden Dauenhauer
//Date: Feb 3, 2025
//Title: Lab4 - Developing multi-threaded applications
//Description: To develop multi-threaded applications and
//             demonstrate the use of pthreads for matrix multiplication

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define N 256
#define M 256
#define L 256

int matrixA[N][M];
int matrixB[M][L];
int matrixC[N][L];

void* multiply_row(void* arg);

int main() {
    // Create random A and B matrices
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrixA[i][j] = rand() % 10;
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < L; j++) {
            matrixB[i][j] = rand() % 10;
        }
    }

    // Create threads for each row
    pthread_t threads[N];
    int row[N];
    for (int i = 0; i < N; i++) {
        row[i] = i;
        pthread_create(&threads[i], NULL, multiply_row, (void*)&row[i]);
    }

    // Wait for all other threads to complete before displaying C matrix
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the C matrix
    printf("matrixC:\n");
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            printf("%4d | ", matrixC[i][j]);
        }
        printf("\n");
    }
    return 0;
}

// Multiply rows
void* multiply_row(void* arg) {
    int i = *((int*)arg);
    for (int j = 0; j < L; j++) {
        int temp = 0;
        for (int k = 0; k < M; k++) {
            temp += matrixA[i][k] * matrixB[k][j];
        }
        matrixC[i][j] = temp;
    }
    pthread_exit(NULL);
}

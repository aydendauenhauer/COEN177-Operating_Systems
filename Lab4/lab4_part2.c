//Name: Ayden Dauenhauer
//Date: Feb 3, 2025
//Title: Lab4 - Developing multi-threaded applications
//Description: To develop multi-threaded applications and
//             demonstrate the use of pthreads for matrix multiplication

/**************************************************************
*    threadHello.c - simple multi-threaded program.           *
*    compile with: gcc threadHello.c -o threadHello           *
**************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 20

void *go(void *);
pthread_t threads[NTHREADS];

int main() {
    static int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, &i);
    printf("Main thread done.\n");
}
void *go(void *arg) {
    printf("Hello from thread %ld with thread ID %d \n", (size_t)pthread_self(), *(int *)arg);
    return (NULL);
}
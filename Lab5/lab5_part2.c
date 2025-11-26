//Name: Ayden Dauenhauer
//Date: Feb 10, 2025
//Title: Lab5 - Synchronization using semaphores, locks, and condition variables
//Description: To use semaphores, mutex locks, and condition variables for synchronization
//             and develop a C program to solve the producer–consumer problem

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock;

void* go(void* arg) {
    pthread_mutex_lock(&lock); //entry section
    printf("Thread %ld Entered Critical Section..\n", (size_t)arg); //critical section
    sleep(1);
    pthread_mutex_unlock(&lock); //exit section
    return (NULL);
}

int main() {
    pthread_mutex_init(&lock, NULL);
    static int i;
    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    }
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
        printf("\t\t\tThread %d returned \n", i);
    }
    printf("Main thread done.\n");
    pthread_mutex_destroy(&lock);
    return 0;
}

//Name: Ayden Dauenhauer
//Date: Feb 10, 2025
//Title: Lab5 - Synchronization using semaphores, locks, and condition variables
//Description: To use semaphores, mutex locks, and condition variables for synchronization
//             and develop a C program to solve the producer–consumer problem

// Thread Sychronization
// To compile this code:
// If using the SCU Linux lab first add #include<fcntl.h>
// Then you're ready to compile.
// gcc lab5_part1.c
// gcc lab5_part1.c -o test

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t *sem;

void* go(void* arg) {
    sem_wait(sem); //entry section
    printf("Thread %ld Entered Critical Section..\n", (size_t)arg); //critical section
    sleep(1);
    sem_post(sem); //exit section
    return (NULL);
}

int main() {
    sem = sem_open("/sem_test", O_CREAT, 0644, 1);
    static int i;
    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    }
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
        printf("\t\t\tThread %d returned \n", i);
    }
    printf("Main thread done.\n");
    sem_unlink("/sem_test");
    return 0;
}

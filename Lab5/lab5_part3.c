//Name: Ayden Dauenhauer
//Date: Feb 10, 2025
//Title: Lab5 - Synchronization using semaphores, locks, and condition variables
//Description: To use semaphores, mutex locks, and condition variables for synchronization
//             and develop a C program to solve the producer–consumer problem

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define n 10

int buffer[n];
int in = 0;
int out = 0;

sem_t full;
sem_t empty;
sem_t lock;

void* producer(void* arg) {
    int i = 0;
    do {
        printf("Produced %d\n", i++);
        sem_wait(&empty);
        sem_wait(&lock);

        buffer[in] = i;
        in = (in + 1) % n;

        sem_post(&lock);
        sem_post(&full);
    } while (1);
    return NULL;
}

void* consumer(void* arg) {
    do {
        sem_wait(&full);
        sem_wait(&lock);

        int i = buffer[out];
        out = (out + 1) % n;

        sem_post(&lock);
        sem_post(&empty);
        printf("Consumed %d\n", i);
    } while (1);
    return NULL;
}

int main() {
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, n);
    sem_init(&lock, 0, 1);

    pthread_t producer_thread;
    pthread_t consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}

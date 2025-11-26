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
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

void* producer(void* arg) {
    int i = 0;
    do {
        printf("Produced %d\n", i++);
        pthread_mutex_lock(&mutex);
        while (count == n) {
            pthread_cond_wait(&empty, &mutex);
        }

        buffer[in] = i;
        in = (in + 1) % n;
        count++;

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    } while (1);
    return NULL;
}

void* consumer(void* arg) {
    do {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&full, &mutex);
        }

        int i = buffer[out];
        out = (out + 1) % n;
        count--;

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        printf("Consumed %d\n", i);
    } while (1);
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    pthread_t producer_thread;
    pthread_t consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}

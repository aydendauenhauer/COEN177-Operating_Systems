//Name: Ayden Dauenhauer
//Date: Jan 13, 2025
//Title: Lab2 - Programming in C and use of Systems Calls
//Description: To develop sample C programs, develop programs with two or more processes
//             using fork( ), exit( ), wait( ), and exec( ) system calls
//             demonstrate the use of light weight processes - threads

#include <stdio.h> /* printf, stderr */
#include <pthread.h> /* thread commands */
#include <unistd.h> /* usleep */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */

// Global variable
int n; // n microseconds to input from keyboard for delay

// Child process
void* child_thread_function(void* arg) {
    for (int i = 0; i < 100; i++) {
        printf("Child process %d\n", i);
        usleep(n);
    }
    return NULL;
}

// Parent process
void* parent_thread_function(void* arg) {
    for (int i = 0; i < 100; i++) {
        printf("\t \t \t Parent Process %d \n",i);
        usleep(n);
    }
    return NULL;
}

/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    n = atoi(argv[1]);
    printf("\nBefore threading.\n");
    pthread_t child_thread, parent_thread;

    // Create threads
    pthread_create(&child_thread, NULL, child_thread_function, NULL);
    pthread_create(&parent_thread, NULL, parent_thread_function, NULL);

    // Wait for threads to finish
    pthread_join(child_thread, NULL);
    pthread_join(parent_thread, NULL);

    return 0;
}
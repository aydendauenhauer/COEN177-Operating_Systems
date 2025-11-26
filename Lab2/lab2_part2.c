//Name: Ayden Dauenhauer
//Date: Jan 13, 2025
//Title: Lab2 - Programming in C and use of Systems Calls
//Description: To develop sample C programs, develop programs with two or more processes
//             using fork( ), exit( ), wait( ), and exec( ) system calls
//             demonstrate the use of light weight processes - threads

#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */

/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t pidA, pidB, pidA1, pidA2, pidB1, pidB2;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\nBefore forking.\n");
    // Create Child A
    pidA = fork();
    // Child A Fork Error
    if (pidA < 0) {
        fprintf(stderr, "Child A fork failed, error %d\n", errno);
    }
    // Child A Process
    else if (pidA == 0) {
        // Create Child A1
        pidA1 = fork();
        // Child A1 Fork Error
        if (pidA1 < 0) {
            fprintf(stderr, "Child A1 fork failed, error %d\n", errno);
        }
        // Child A1 Process
        else if (pidA1 == 0) {
            printf("Grandchild Process A1: PID=%d, PPID=%d, children=NA\n", getpid(), getppid());
        }
        // Parent (Child A) Process
        else {
            // Create Child A2
            pidA2 = fork();
            // Child A2 Fork Error
            if (pidA2 < 0) {
                fprintf(stderr, "Child A2 fork failed, error %d\n", errno);
            }
            // Child A2 Process
            else if (pidA2 == 0) {
                printf("Grandchild Process A2: PID=%d, PPID=%d, children=NA\n", getpid(), getppid());
            }
            // Parent (Child A) Process
            else {
                printf("Child Process A: PID=%d, PPID=%d, children=%d,%d\n", getpid(), getppid(), pidA1, pidA2);
                usleep(n);
            }
        }
    }
    // Original Parent Process
    else {
        // Create Child B
        pidB = fork();
        // Child B Fork Error
        if (pidB < 0) {
            fprintf(stderr, "Child B fork failed, error %d\n", errno);
        }
        // Child B Process
        else if (pidB == 0) {
            // Create Child B1
            pidB1 = fork();
            // Child B1 Fork Error
            if (pidB1 < 0) {
                fprintf(stderr, "Child B1 fork failed, error %d\n", errno);
            }
            // Child B1 Process
            else if (pidB1 == 0) {
                printf("Grandchild Process B1: PID=%d, PPID=%d, children=NA\n", getpid(), getppid());
            }
            // Parent (Child B) Process
            else {
                // Create Child B2
                pidB2 = fork();
                // Child B2 Fork Error
                if (pidB2 < 0) {
                    fprintf(stderr, "Child B2 fork failed, error %d\n", errno);
                }
                // Child B2 Process
                else if (pidB2 == 0) {
                    printf("Grandchild Process B2: PID=%d, PPID=%d, children=NA\n", getpid(), getppid());
                }
                // Parent (Child B) Process
                else {
                    printf("Child Process B: PID=%d, PPID=%d, children=%d,%d\n", getpid(), getppid(), pidB1, pidB2);
                    usleep(n);
                }
            }
        }
        // Original Parent Process
        else {
            printf("Original Parent: PID=%d, PPID=NA, children=%d,%d\n", getpid(), pidA, pidB);
            usleep(n);
            usleep(n);
        }
    }
    return 0;
}
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
    pid_t pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\nBefore forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
    else if (pid == 0) {
        execlp("/bin/ls", "ls", NULL);
    }
    else {
        wait(NULL);
        printf("Child Complete");
        exit(0);
    }
    return 0;
}
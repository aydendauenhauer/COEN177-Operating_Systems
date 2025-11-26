//Name: Ayden Dauenhauer
//Date: Feb 2, 2025
//Title: Homework 2
//Description: time.c determines the amount of time necessary to run a command from the command line.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int fds[2];
    printf("\n Before forking.\n");

    if (pipe(fds) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        return 1;
    }

    else if (pid == 0) {
        close(fds[0]);

        struct timeval start;
        if (gettimeofday(&start, NULL) == -1) {
            perror("gettimeofday");
            return 1;
        }

        if (write(fds[1], &start, sizeof(start)) == -1) {
            perror("write to pipe");
            close(fds[1]);
        }

        close(fds[1]);

        execvp(argv[1], &argv[1]);
        fprintf(stderr, "Failed to exec %s: %s\n", argv[1], strerror(errno));
    }

    else {
        close(fds[1]);

        if (wait(NULL) < 0) {
            perror("wait");
            close(fds[0]);
        }

        struct timeval end;
        if (gettimeofday(&end, NULL) == -1) {
            perror("gettimeofday");
            close(fds[0]);
        }

        struct timeval start;
        ssize_t bytesRead = read(fds[0], &start, sizeof(start));

        if (bytesRead < 0) {
            perror("read from pipe");
            close(fds[0]);
        }

        else if (bytesRead == 0) {
            fprintf(stderr, "No data read from child.\n");
            close(fds[0]);
        }
        close(fds[0]);

        double elapsed = (double)(end.tv_sec - start.tv_sec) +
                         (double)(end.tv_usec - start.tv_usec) / 1000000.0;

        printf("Elapsed time: %.5f\n", elapsed);
        return 0;
    }
}

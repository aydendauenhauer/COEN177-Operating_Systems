//Name: Ayden Dauenhauer
//Date: Jan 27, 2025
//Title: Lab3 - Pthreads and inter-process Communication: Pipes
//Description: To develop multi-process application programs,
//             demonstrate the use of pipes as an inter-process communication (IPC) mechanism,
//             demonstrate the use of pthreads

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fds[2];
    char buff[60];
    pipe(fds);

    if (fork()==0) {
        // Child process: producer
        close(fds[0]);
        char message[] = "producer";
        write(fds[1], message, strlen(message) + 1);
        close(fds[1]);
        exit(0);
    }
    else {
        // Parent process: consumer
        close(fds[1]);
        while(1){
            int n = read(fds[0], buff, 60);
            printf("consumer received: %s\n", buff);
        }
        close(fds[0]);
        wait(NULL);
        exit(0);
    }

    return 0;
}
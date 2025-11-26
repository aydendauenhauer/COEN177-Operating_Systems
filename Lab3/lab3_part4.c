//Name: Ayden Dauenhauer
//Date: Jan 27, 2025
//Title: Lab3 - Pthreads and inter-process Communication: Pipes
//Description: To develop multi-process application programs,
//             demonstrate the use of pipes as an inter-process communication (IPC) mechanism,
//             demonstrate the use of pthreads

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int fds[2];
	pipe(fds);
	/*child 1 duplicates downstream into stdin */
	if (fork() == 0) {
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("grep", "grep", "root", 0);
	}
	/*child 2 duplicates upstream into stdout */
	else if (fork() == 0) {
		dup2(fds[1], 1);
		close(fds[0]);
		execlp("cat", "cat", "/etc/passwd", 0);
	}
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
}

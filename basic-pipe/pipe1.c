#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {

	int pc_pipe[2];
	if (pipe(pc_pipe) == -1) {
		fprintf(stderr, "ERROR: Failed to create pipe\n");
	}

	pid_t child_pid = fork();
	/* If child process... */
	if (child_pid == 0) {
		/* Close the reading end of the pipe for the child since it will never
		 * read */
		close(pc_pipe[0]);
		/* Redirect stdout for the program we are about to exec() to the write
		 * end of the pipe we created */
		dup2(pc_pipe[1], STDOUT_FILENO);

		/* execute a basic shell command that generates output to stdout */
		execlp("cat", "cat", "pipe1.c", (char *) NULL);

		/* If this point is reached, the execl() command failed */
		fprintf(stderr, "ERROR: execl() failed\n");
		exit(-1);
	/* If parent process... */
	} else {
		/* RFC: Read from the pipe what the child process sent (its own
		 * redirected stdout), and then write it to the parent's stdout */
		/* RFC1: Close the writing end of the pipe for the parent since it will
		 * never write */
		close(pc_pipe[1]);

		/* RFC2: Read a byte from the child's output and immediately write it
		 * to the parent's stdout */
		char recv_buf;
		while (read(pc_pipe[0], &recv_buf, 1) > 0) {
			write(STDOUT_FILENO, &recv_buf, 1);
		}

		/* RFC3: Close the reading end of the pipe as we are done reading from
		 * it */
		close(pc_pipe[0]);
	}

	return 0;
}

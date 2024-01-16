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
		execlp("cat", "cat", "pipe2.c", (char *) NULL);

		/* If this point is reached, the execl() command failed */
		fprintf(stderr, "ERROR: execl() failed\n");
		exit(-1);
	/* If parent process... */
	} else {
		/* RFC: Read from child process the result */
		/* RFC1: Close the writing end of the pipe for the parent since it will
		 * never write */
		close(pc_pipe[1]);

		/* RFC2: Read all content from the output of the child process and
		 * store it in a dynamically resizing array for later use */
		ssize_t recv_buf_size = 1024; /* Array size begins at 1024 */
		char * recv_buf = (char *) malloc(recv_buf_size);
		ssize_t recv_len = 0; /* This represents the number of elements in the array */
		ssize_t ret = 0; /* This will be used to store how many bytes the read() call read */

		while ((ret = read(pc_pipe[0], &recv_buf[recv_len], 1024)) > 0) {
			recv_len += ret;
			/* If it doesn't have space for a full read attempt, enlarge the
			 * receiving buffer by doubling its size  */
			if (recv_buf_size - recv_len < 1024) {
				recv_buf_size *= 2;
				recv_buf = (char *) realloc(recv_buf, recv_buf_size);
				if (recv_buf == NULL) {
					fprintf(stderr, "ERROR: failed to realloc recv buffer\n");
				}
			}
		}
		/* RFC3: Close the reading end of the pipe as we are done reading from
		 * it */
		close(pc_pipe[0]);

		/* At this point we have a char array 'recv_buf' with 'recv_len'
		 * elements that we can do with as we please. For this program, we'll
		 * just print them */
		for (int i = 0; i < recv_len; i++) {
			printf("%c", recv_buf[i]);
		}
	}

	return 0;
}

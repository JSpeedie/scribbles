#include <arpa/inet.h> // for inet_aton()
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int client_fd;
	int port;
	struct sockaddr_in server_address;
	// char buffer[1024] = { 0 }; // TODO: unused

	/* Parse commandline arguments */
	if (argc != 3){
		fprintf(stderr, "ERROR: Invalid Number of Arguments...\nUsage: ./client <server-ip-address> <server-listen-port>\n");
		exit(-1);
	}
	sscanf(argv[2], "%d", &port);
	/* Set server address information for host */
	server_address.sin_family = AF_INET; // IPv4
	server_address.sin_port = htons(port); // Host-to-Network for port number
	inet_pton(AF_INET, argv[1], &server_address.sin_addr);

	/* Create IPv4, TCP socket */
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "ERROR: failed to create socket\n");
		exit(-1);
	}

	int status = 0;
	if ((status = connect(client_fd, (struct sockaddr *) &server_address, sizeof(server_address))) < 0) {
		/* Did NOT Connect successfully */
		fprintf(stderr, "ERROR: Failed to connect\n");
		return -1;
	/* Connected successfully */
	} else {
		printf("Connected!\n");
	}

	return 0;
}

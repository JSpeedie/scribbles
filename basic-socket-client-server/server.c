#include <arpa/inet.h> // for inet_aton()
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int server_fd, new_socket;
	int port;
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	// char buffer[1024] = { 0 }; // TODO: unused

	/* Parse commandline arguments */
	if (argc != 2){
		fprintf(stderr, "ERROR: Invalid Number of Arguments...\nUsage: ./server <server-listen-port>\n");
		exit(-1);
	}
	sscanf(argv[1], "%d", &port);

	/* Create IPv4, TCP socket */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "ERROR: failed to create socket\n");
		exit(-1);
	}

	/* Set options for socket so it reuses the address and port */
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, \
		sizeof(opt))) {

		fprintf(stderr, "ERROR: failed to set socket to reuses address and port\n");
		exit(-1);
	}

	/* Set address information for host address */
	address.sin_family = AF_INET; // IPv4
	address.sin_port = htons(port); // Host-to-Network for port number
	address.sin_addr.s_addr = INADDR_ANY; // Set address to any available one given by the system
	/* alternatively(?): */
	/* inet_aton("63.161.169.137", &address.sin_addr); */

	/* Bind server */
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		fprintf(stderr, "ERROR: failed to bind socket\n");
		exit(-1);
	}
	/* Set socket as passive (one that listens) with a backlog of 3 */
	if (listen(server_fd, 3) < 0) {
		fprintf(stderr, "ERROR: failed to listen on socket\n");
		exit(-1);
	}
	while (1) {
		/* Wait for new client */
		if ((new_socket = accept(server_fd, (struct sockaddr *) &address, &addrlen)) < 0) {
			/* New client did NOT connect successfully */
			fprintf(stderr, "ERROR: on new client connection\n");
			exit(-1);
		/* New client connected successfully */
		} else {
			printf("received a new client!\n");
			// TODO: anything that should be done upon receiving a new client connection
		}
	}

	return 0;
}

# gcc flags for includes
INCS = -I. -I/usr/include
LIBS = -L/usr/lib
# Flags
CFLAGS = -Wall
# Compiler and linker
CC = gcc -ggdb
# CC = gcc

# `compile` first because we want `make` to just compile the program, and the
# default target is always the the first one that doesn't begin with "."
compile: server client

server: server.c
	$(CC) $(CFLAGS) server.c $(INCS) $(LIBS) -o server

client: client.c
	$(CC) $(CFLAGS) client.c $(INCS) $(LIBS) -o client

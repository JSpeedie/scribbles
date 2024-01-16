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
compile: pipe1 pipe2

pipe1: pipe1.c
	$(CC) $(CFLAGS) pipe1.c $(INCS) $(LIBS) -o pipe1

pipe2: pipe2.c
	$(CC) $(CFLAGS) pipe2.c $(INCS) $(LIBS) -o pipe2

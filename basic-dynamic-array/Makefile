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
compile:
	$(CC) $(CFLAGS) dynamic-array.c $(INCS) $(LIBS) -o dynamic-array

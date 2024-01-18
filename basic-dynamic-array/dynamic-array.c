#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dynamic-array.h"

char CMD_QUIT[] = { "quit" };
char CMD_PRINT[] = { "print" };


int main() {
	/* The number of elements in the array */
	int array_ne = 0;
	/* The maximum number of elements the array can fit, set to some sensible default */
	int array_size = DEFAULT_ARRAY_SIZE;
	/* I use calloc() here rather than malloc only because I wish to print out
	 * the full array, past the last element. */
	char *array = (char *) calloc(array_size, (MAX_ENTRY_SIZE + 1));
	/* But since this array knows precisely where its last meaningful entry is,
	 * normally we would just malloc() and never access the unused spots:
	 *
	 *	char *array = (char *) malloc( (MAX_ENTRY_SIZE + 1) * array_size);
	 *
	 */
	if (array == NULL) {
		fprintf(stderr, "ERROR: could not allocate array\n");
		return -1;
	}

	char buffer[MAX_ENTRY_SIZE + 1];

	while (1) {
		fprintf(stdout, "Enter the next string you would like to append to the array (or \"quit\" to terminate the program or \"print\" to print the array): ");
		/* Read a line from stdin */
		char *ret = fgets(buffer, sizeof(buffer), stdin);
		if (ret == NULL) {
			fprintf(stderr, "ERROR: could not read input\n");
			return -1;
		}

		/* Replace newline character with null terminator since we only want
		 * the string the user entered, not them hitting the enter key too */
		ret = strchr(buffer, '\n');
		(*ret) = '\0';

		/* If the user wants to quit the program */
		if (strncmp(buffer, CMD_QUIT, strlen(CMD_QUIT)) == 0) {
			break;
		/* If the user wants to print the array */
		} else if (strncmp(buffer, CMD_PRINT, strlen(CMD_PRINT)) == 0) {
			/* For looping through known elements rather than all
			 * elements/spots indiscriminantly:
			 *
			 *	for (int i = 0; i < array_ne; i++) {
			 *
			 */
			fprintf(stdout, "[ ");

			for (int i = 0; i < array_size; i++) {
				if (i < array_size - 1) {
					fprintf(stdout, "\"%s\", ", &(array[i * (MAX_ENTRY_SIZE + 1)]));
				} else {
					fprintf(stdout, "\"%s\"", &(array[i * (MAX_ENTRY_SIZE + 1)]));
				}
			}

			fprintf(stdout, " ]\n");

		/* If the user entered a non-command string, one that should be
		 * appended to the array */
		} else {

			/* If there is no space to add a new element to the array, resize the
			* array via realloc() */
			if (array_ne + 1 > array_size) {
				array_size = (2 * array_size) + 1; /* 2n + 1 resizing */
				array = \
					(char *) realloc(array, (MAX_ENTRY_SIZE + 1) * array_size);
				if (array == NULL) {
					fprintf(stderr, "ERROR: could not resize array\n");
					return -1;
				}
			}
			strncpy( \
				&array[array_ne * (MAX_ENTRY_SIZE + 1)], \
				&buffer[0], MAX_ENTRY_SIZE);
			array_ne++;
		}
	}

	return 0;
}

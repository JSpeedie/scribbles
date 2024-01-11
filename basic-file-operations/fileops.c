#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CHUNK 1024

/** Takes a string representing a path to a file 'filepath' and reads
 * 'num_bytes' of the file into '*ret'.
 *
 * \param '*filepath' the file path for the file to be read.
 * \param 'num_bytes' the number of bytes to be read by the function.
 * \param '*ret' the char pointer the contents of the file will be read into.
 * \return negative int if there was an error, 0 if all the bytes were
 *     successfully read.
 */
int read_bytes(char * filepath, size_t num_bytes, unsigned char * ret) {
	/* Open the file */
	FILE * f = fopen(filepath, "r+");
	if (f == NULL) {
		fprintf(stderr, "ERROR: read_bytes(): could not open file \"%s\"\n", filepath);
		return -1;
	}

	/* Read from the file */
	size_t nmem_read = 0;
	if (num_bytes != (nmem_read = fread(ret, 1, num_bytes, f)) ) {
		fprintf(stderr, "ERROR: read_bytes(): could not read %lu bytes, was only able to read %lu\n", num_bytes, nmem_read);
		fclose(f);
		return -1;
	}

	fclose(f);
	return 0;
}


/** Takes an already open FILE and reads 'num_bytes' into 'char * ret'.
 *
 * \param '*f' the (already open) FILE to be read.
 * \param 'num_bytes' the number of bytes to be read by the function.
 * \param '*ret' the char pointer the contents of the file will be read into.
 * \return negative int if there was an error, 0 if all the bytes were
 *     successfully read.
 */
int read_bytes_open_file(FILE * f, size_t num_bytes, unsigned char * ret) {
	size_t nmem_read = 0;
	if (num_bytes != (nmem_read = fread(ret, 1, num_bytes, f)) ) {
		fprintf(stderr, "ERROR: read_bytes_open_file(): could not read %lu bytes, was only able to read %lu\n", num_bytes, nmem_read);
		return -1;
	}

	return 0;
}


/** Takes an already open FILE and reads 'num_bytes' into a malloc'd array
 * which this function returns and which must be freed by the caller of this
 * function.
 *
 * \param '*f' the file path for the file to be read.
 * \param '*ret_len' the number of bytes read by the function. This function
 *     will modify this argument.
 * \return a char pointer that represents an array of 'ret_len' length
 *     containing the contents of the file which were read. If there was an
 *     error, the char pointer will be NULL and 'ret_len' will be unchanged.
 */
unsigned char * read_chunk_of_file(FILE * f, uint64_t * ret_len) {
	unsigned char * ret = malloc(MAX_CHUNK);
	/* If the alloc call failed, exit */
	if (ret == NULL) {
		fprintf(stderr, "ERROR: read_chunk_of_file(): could not allocate buffer for file\n");
		return NULL;
	}

	/* Read from the file */
	size_t nmem_read = fread(&ret[0], 1, MAX_CHUNK, f);

	/* Modify return arguments */
	*ret_len = nmem_read;

	return ret;
}


/** Writes nothing (i.e., "") to a file, clearing it.
 *
 * \param '*filepath' the file path for the file to be wiped.
 * \return negative int if there was an error, 0 if the file was successfully
 *     cleared.
 */
int clear_file(char * filepath) {
	FILE * victim = fopen(filepath, "w");
	/* If the file could not be opened, exit */
	if (victim == NULL) {
		fprintf(stderr, "ERROR: clear_file(): could not open target file\n");
		return -1;
	}
	fprintf(victim, "");
	fclose(victim);

	return 0;
}

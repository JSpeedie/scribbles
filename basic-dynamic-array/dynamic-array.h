/* This should be a sensible size for the array. Too small and typical usage
 * will result in lots of resizes, too large and lots of memory will be given
 * to the program that will never be used. I use 2 as the default for this
 * program only to make it easy to demonstrate the array resizing */
#define DEFAULT_ARRAY_SIZE 2
#define MAX_ENTRY_SIZE 128

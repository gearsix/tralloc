/**
 * See README.md for documentation
**/

#ifndef STDLIBW
#define STDLIBW

#include <stdlib.h>
#include <assert.h>

/* num. bytes heap-allocated by htrack */
size_t htrack_siz();

/* the max. number of heap-allocated bytes htrack will allow */
size_t htrack_limit();

/* set the max. number of heap-allocated bytes htrack will allow, 0 = infinite */
size_t htrack_setlimit(size_t n);

/* The number of bytes allocated for `ptr`.
 * ptr MUST be allocated by htrack */
size_t htrack_allocsiz(void *ptr);

/**
 * stdlib wrappers - behave the same as their stdlib counterparts
**/
void *htrack_malloc(size_t n);

void *htrack_calloc(size_t num, size_t n);

/* ptr MUST be allocated by htrack */
void *htrack_realloc(void *ptr, size_t n);

/* ptr MUST be allocated by htrack */
void htrack_free(void *ptr);

#endif

/* See README.md for documentation
 *
 * IMPORTANT: Any `ptr` value used *must* be allocated by
 * tralloc or you'll run into problems.
 */

#ifndef TRALLOC
#define TRALLOC

#include <stdlib.h>
#include <assert.h>

/* num. bytes heap-allocated by tralloc */
size_t tr_siz();

/* the max. number of heap-allocated bytes tralloc will allow */
size_t tr_limit();

/* set the max. number of heap-allocated bytes tralloc will allow, 0 = infinite */
size_t tr_setlimit(size_t n);

/* The number of bytes allocated for `ptr` */
size_t tr_allocsiz(void *ptr); 

/* stdlib wrappers
 * These behave the same as their stdlib counterparts */
void *tr_malloc(size_t n);

void *tr_calloc(size_t num, size_t n);

void *tr_realloc(void *ptr, size_t n); 

void tr_free(void *ptr); 

#endif

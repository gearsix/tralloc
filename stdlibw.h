#ifndef STDLIBW
#define STDLIBW

#include <stdlib.h>
#include <assert.h>

/** heapsiz - heap size?
 * returns the currently tracked `heapsiz`
**/
size_t heapsiz();

/** heaplim - heapsiz limit?
 * returns the current limit set on `heapsiz`.
 * if 0 is returned, there is no limit.
**/
size_t heaplim();

/** limheap - limit heapsiz
 * set the limit on `heapsiz` to `siz`, returns the set limit.
 * if the returned value is not `n`, then the call failed.
**/
size_t limheap(size_t n);

/**
 * sizeofw - sizeof (wrapper)
 * returns the number of allocated bytes for `ptr`.
 * will fail if called on a pointer not allocated by stdlibw.
**/
size_t sizeofw(void *ptr);

/** mallocw - malloc (wrapper)
 * malloc (sizeof(size_t) + siz) bytes and return [1] of that pointer.
 * [0] is used to store `siz` for other stdlibw operations.
 * `(siz + sizeof(size_t))` will be added to tracked `heapsiz`.
**/
void *mallocw(size_t siz);

/** callocw - calloc (wrapper)
 * see `mallocw()`. Duplicate, but for `calloc`.
**/
void *callocw(size_t num, size_t siz);

/** reallocw - realloc (wrapper)
 * `mallocw()` a new pointer, copy `ptr` contents to it and `freew()`
 * ptr.
**/
void *reallocw(void *ptr, size_t siz);

/** freew - free (wrapper)
 * free a pointer allocated by a *stdlibw* alloc function.
**/
void freew(void *ptr);

#endif

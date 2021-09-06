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
 * sizeofw - sizeof wrapper
 * returns the number of allocated bytes for `ptr`.
 * will fail if called on a pointer not allocated by stdlibw.
**/
size_t sizeofw(void *ptr);

/** mallocw - malloc wrapper
 * malloc (sizeof(size_t) + siz) bytes and return that pointer from [1]
 * [0] is used to store `siz`.
 * `(siz + sizeof(size_t))` will be added to `heapsiz`
**/
void *mallocw(size_t siz);

void *callocw(size_t num, size_t siz);

void *reallocw(void *ptr, size_t siz);

void freew(void *ptr);

#endif

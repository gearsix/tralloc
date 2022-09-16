
# tralloc - track allocations

An C libray for tracking the size of heap-allocated memory blocks.

This is more of a proof-of-concept than anything and I wouldn't
recommend using it in production. There's an accompanying article
here:
[Tracking Allocations in C](gearsix.net/software/tracking-allocations-in-c/)


## Overview

This library provides several functions that act as wrappers
around the _stdlib_ memory allocation functions to provide
information on the number of heap-allocated bytes for individual
pointers and overall.

It's implemented with functions the act as _stdlib_ wrappers so
that it can sit ontop of whatever _stdlib_ implementation you're
using. The downside of this is that it's unable to track any
allocations made without these wrappers.

There are also a few usability pitfalls:
- If you call some of the functions on pointers that **have not**
been allocated by tralloc allocation functions, then it'll probably
cause a memory error.
This behaviour is consistent with stdlib though. Make sure to read
function documentation.
- If you use a *tralloc* pointer to an address that wasn't returned
by tralloc (either from incrementing/decrementing it), then it'll
cause a memory error.

This was done more as a personal exercise than anything, most of the
time in C you'll track allocated memory yourself. This was just a
cool idea I got carried away with.


## Goals

- Track the total number of heap-allocated bytes.
- Track number of bytes allocated for individual memory blocks.
- Don't get in the way of any users, behave as regular stdlib.


## Guidelines

- **Do not** call `tralloc_realloc()`, `tralloc_allocsiz()` or
`tralloc_free` on an address not returned by one of the tralloc stdlib
wrapper functions.
- Don't expect tralloc to work on a non-tralloc pointer address.
- You should be able to use the _tralloc stdlib wrappers_ just as you
would use their stdlib counterparts without error.
- If you want to use `malloc` instead of `tr_malloc`, use a macro.
See `test.c` for an example of this.
- It's experimental, so don't do anything silly and expect it to work.


## API

**tralloc_siz**

	size_t tralloc_siz();

Returns the number of bytes heap-allocated by *tralloc memory allocation*
functions.

**tralloc_limit**

	size_t tralloc_limit();

Returns the maximum limit set on `tralloc_siz`.
If 0 is returned, there is no limit (returns 0 by default).

**tralloc_setlimit**

	size_t tralloc_setlimit(size_t n);

Sets the maximum limit on `tralloc_siz`.
If this limit is reached, then tralloc alloc functions will fail and
return NULL.
Returns `n` if successful and 0 if unsuccessful.

**tralloc_allocsiz**

	size_t tralloc_allocsiz(void *ptr);

Returns number of bytes allocated for `ptr`.

> `ptr` **must** be a the address returned by a tralloc allocation.


### stdlib wrappers

These functions behave exactly the same and their stdlib counterparts.
The only difference is that they will also add the memory overhead
required to track the number of allocated bytes for each pointer
(which `sizeof(size_t)` per-pointer) and increment/decrement the
tracked heapsiz accordingly.
This overhead is stored at index [-1] of the returned pointers and
used by functions within the library for tracking the heapsiz.

**tralloc_malloc**

	void *tralloc_malloc(size_t n);

**tralloc_calloc**

	void *tralloc_calloc(size_t num, size_t n);

**tralloc_realloc**

	void *tralloc_realloc(void *ptr, size_t n);

> `ptr` **must** be a the address returned by a tralloc allocation.

**tralloc_free**

	void tralloc_free(void *ptr);

> `ptr` **must** be a the address returned by a tralloc allocation.

## Authors

- gearsix



# htrack

An ANSI-C libray for tracking heap-allocated memory.

## Overview

This library provides several functions that act as wrappers
around the _stdlib_ memory allocation functions to track and
provide information on the number of heap-allocated bytes for
individual pointers and overall.

It's implemented with functions the act as _stdlib_ wrappers so
that it can sit ontop of whatever _stdlib_ implementation you're
using. The downside of this is that it's unable to track any
allocations made without these wrappers. This is acceptable since
it's intended to be used for tracking allocations made by yourself.

There are also a few usability pitfalls: if you call some of the
functions on pointers that **have not** been allocated by htrack
allocation functions, then it'll cause a memory error.
This behaviour is consistent with stdlib though. Make sure to read
function documentation.

This was done more as a personal exercise than anything, most of the
time in C you'll track allocated memory yourself. This was just a
cool idea I got carried away with.

## Goals

- Track the total number of heap-allocated bytes.
- Track number of bytes allocated for individual pointers.
- Don't get in the way of any users.

## Guidelines

- **Do not** call `htrack_realloc()`, `htrack_allocsiz()` or
`htrack_free` on a pointer not allocated by one of the htrack stdlib
wrapper functions (same way you wouldn't call free on a pointer you
didn't allocate with stdlib). Otherwise you'll probably run into a
segfault.
- Don't expect htrack to track memory allocated outside of it's own
htrack functions.
- You should be able to use the _htrack stdlib wrappers_ just as you
would use their stdlib counterparts without error.

## API

**htrack_siz**

	size_t htrack_siz();

Returns the number of bytes heap-allocated by _htrack memory allocation_
functions.

**htrack_limit**

	size_t htrack_limit();

Returns the maximum limit set on `htrack_siz`.
If 0 is returned, there is no limit (returns 0 by default).

**htrack_setlimit**

	size_t htrack_setlimit(size_t n);

Sets the maximum limit on `htrack_siz`.
If this limit is reached, then htrack alloc functions will fail and
return NULL.
Returns `n` if successful and 0 if unsuccessful.

**htrack_allocsiz**

	size_t htrack_allocsiz(void *ptr);

Returns number of bytes allocated for `ptr`.

> `ptr` **must** be a _htrack allocated pointer_.

### stdlib wrappers

These functions behave exactly the same and their stdlib counterparts.
The only difference is that they will also add the memory overhead
required to track the number of allocated bytes for each pointer
(which `sizeof(size_t)` per-pointer) and increment/decrement the
tracked heapsiz accordingly.
This overhead is stored at index [-1] of the returned pointers and
used by functions within the library for tracking the heapsiz.

**htrack_malloc**

	void *htrack_malloc(size_t n);

**htrack_calloc**

	void *htrack_calloc(size_t num, size_t n);

**htrack_realloc**

	void *htrack_realloc(void *ptr, size_t n);

> `ptr` **must** be a pointer allocated by htrack.

**htrack_free**

	void htrack_free(void *ptr);

> `ptr` **must** be a pointer allocated by htrack.

## Authors

- gearsix


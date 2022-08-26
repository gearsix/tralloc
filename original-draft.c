/* htrack.c
 * example of how to track heap-heapsiz during runtime
 * -gearsix
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t heapsiz = 0;

// mallocw (malloc wrapper) allocates nbytes + sizeof(size_t).
// the allocated number of bytes for the pointer is stored in [0],
// the memory block requested by the user is stored from [1]..[n].
// note that ptr[1] is returned.
void *mallocw(size_t nbytes)
{
	nbytes += sizeof(size_t);
	heapsiz += nbytes;
	size_t *ptr = malloc(nbytes);
	ptr[0] = nbytes;
	return &ptr[1];
}

// sizeofw (sizeof wrapper) check [-1] for the size_t value set by
// mallocw. ptr must have been allocated by mallocw to avoid issues.
size_t sizeofw(void *ptr)
{
	return ((size_t *)ptr)[-1];
}

// freew (free wrapper) frees *ptr from [-1], will probably cause
// an issue if the ptr wasn't allocated by mallocw.
void freew(void *ptr)
{
	heapsiz -= sizeofw(ptr);
	free((size_t *)ptr-1);
}

int main(int argc, char *argv[])
{
	printf("heapsiz: %lu\n", heapsiz);

	char *str = mallocw(6);
	if (str == NULL) {
		fprintf(stderr, "mallocw failed");
		return EXIT_FAILURE;
	}
	strcpy(str, "foobar");
	printf("str = '%s', strlen %d, sizeof %d\n", str, strlen(str), sizeofw(str));
	printf("heapsiz: %lu\n", heapsiz);
	puts("freeing str...");
	freew(str);
	printf("heapsiz: %lu\n", heapsiz);

	return EXIT_SUCCESS;
}

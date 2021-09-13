#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "htrack.h"

void fail(const char *msg)
{
	fprintf(stderr, msg);
	exit(EXIT_FAILURE);
}

int main (int argc, char *argv[])
{
	size_t siz;
	char *str;

	printf("htrack_siz: %lu\n", htrack_siz());
	if (htrack_siz() != 0) fail("initial htrack_siz not 0\n");
	printf("htrack_limit: %lu\n", htrack_limit());
	if (htrack_limit() != 0) fail("initial htrack_setlimit not 0\n");

	siz = 6;
	str = htrack_malloc(siz);
	printf("str = '%s', %zu bytes\n", str, htrack_allocsiz(str));
	if (str == NULL) fail("htrack_malloc failed\n");
	if (htrack_allocsiz(str) != (siz + sizeof(size_t))) fail("invalid htrack_allocsiz value\n");
	strcpy(str, "foobar");
	if (strcmp(str, "foobar") != 0) fail("strcpy failed\n");
	printf("str = '%s', %zu bytes\n", str, htrack_allocsiz(str));

	siz = 12;
	str = htrack_realloc(str, siz);
	printf("str = '%s', %zu bytes\n", str, htrack_allocsiz(str));
	if (str == NULL) fail("htrack_realloc failed\n");
	if (htrack_allocsiz(str) != (siz + sizeof(size_t))) fail("invalid htrack_allocsiz value\n");
	strcpy(str, "foobarfoobar");
	if (strcmp(str, "foobarfoobar") != 0) fail("strcpy failed\n");
	printf("str = '%s', %zu bytes\n", str, htrack_allocsiz(str));

	htrack_free(str);

	siz = 6;
	htrack_setlimit(10);
	str = htrack_calloc(2, siz); /* should cause assertion failure */
	printf("str = '%s', %zu bytes\n", str, htrack_allocsiz(str));
	htrack_free(str);
	

	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tralloc.h"

void fail(const char *msg)
{
	fprintf(stderr, msg);
	exit(EXIT_FAILURE);
}

int main (int argc, char *argv[])
{
	size_t siz;
	char *str;

#ifdef TRALLOC_WRAP /* example of how to replace stdlib functions */
	#define malloc(n)		tr_malloc(n)
	#define calloc(num, n)	tr_calloc(num, n)
	#define realloc(ptr, n)	tr_realloc(ptr, n)
	#define free(ptr)		tr_free(ptr)

	test_tralloc_wrap (); /* calls malloc, calloc, realloc, free */
#else
	test_tralloc();
#endif

	return EXIT_SUCCESS;
}

void test_tralloc()
{
	printf("tr_siz: %lu, tr_limit: %lu\n", tr_siz(), tr_limit());
	if (tr_siz() != 0) fail("initial tr_siz not 0\n");
	if (tr_limit() != 0) fail("initial tr_setlimit not 0\n");

	siz = 6;
	str = tr_malloc(siz);
	printf("str = '%s', %zu bytes\n", str, tr_allocsiz(str));
	if (str == NULL) fail("tr_malloc failed\n");
	if (tr_allocsiz(str) != (siz + sizeof(size_t))) fail("invalid tr_allocsiz value\n");
	strcpy(str, "foobar");
	if (strcmp(str, "foobar") != 0) fail("strcpy failed\n");
	printf("str = '%s', %zu bytes\n", str, tr_allocsiz(str));

	siz = 12;
	str = tr_realloc(str, siz);
	printf("str = '%s', %zu bytes\n", str, tr_allocsiz(str));
	if (str == NULL) fail("tr_realloc failed\n");
	if (tr_allocsiz(str) != (siz + sizeof(size_t))) fail("invalid tr_allocsiz value\n");
	strcpy(str, "foobarfoobar");
	if (strcmp(str, "foobarfoobar") != 0) fail("strcpy failed\n");
	printf("str = '%s', %zu bytes\n", str, tr_allocsiz(str));

	tr_free(str);

	siz = 6;
	tr_setlimit(10);
	puts("the following should cause an assertion failure:");
	fflush(stdout);
	str = tr_calloc(2, siz); /* should cause assertion failure */
	printf("str = '%s', %zu bytes\n", str, tr_allocsiz(str));
	tr_free(str);
}

void test_tralloc_wrap()
{
	printf("tr_siz: %lu, tr_limit: %lu\n", tr_siz(), tr_limit());
	if (tr_siz() != 0) fail("initial tr_siz not 0\n");
	if (tr_limit() != 0) fail("initial tr_setlimit not 0\n");

	siz = 6;
	str = malloc(siz);
	printf("str = '%s', %zu bytes\n", str, tr_allocsiz(str));
	if (str == NULL) fail("malloc failed\n");
	if (tr_allocsiz(str) != (siz + sizeof(size_t))) fail("invalid tr_allocsiz value\n");
	strcpy(str, "foobar");
	if (strcmp(str, "foobar") != 0) fail("strcpy failed\n");
	printf("str = '%s', %zu bytes\n", str, tr_allocsiz(str));

	siz = 12;
	str = realloc(str, siz);
	printf("str = '%s', %zu bytes\n", str, tr_allocsiz(str));
	if (str == NULL) fail("realloc failed\n");
	if (tr_allocsiz(str) != (siz + sizeof(size_t))) fail("invalid tr_allocsiz value\n");
	strcpy(str, "foobarfoobar");
	if (strcmp(str, "foobarfoobar") != 0) fail("strcpy failed\n");
	printf("str = '%s', %zu bytes\n", str, tr_allocsiz(str));

	free(str);

	siz = 6;
	tr_setlimit(10);
	puts("the following should cause an assertion failure:");
	fflush(stdout);
	str = calloc(2, siz); /* should cause assertion failure */
	printf("str = '%s', %zu bytes\n", str, tr_allocsiz(str));
	free(str);
}


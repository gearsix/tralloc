#include "stdlibw.h"

static size_t _heap(char op, size_t n)
{
	static size_t siz = 0, lim = 0;
	switch (op) {
		case 0:   break;
		case '!': return (lim = n);
		case '?': return lim;
		case '+':
			if (lim > 0) assert(siz + n <= lim);
			siz += n;
			break;
		case '-':
			if (lim > 0) assert(siz - n >= lim);
			siz -= n;
			break;
		default: /* invalid op */
			assert(1);
	}
	return siz;
}

size_t heapsiz()
{
	return _heap(0, 0);
}

size_t heaplim()
{
	return _heap('?', 0);
}

size_t limheap(size_t n)
{
	return _heap('!', 0);
}

size_t sizeofw(void *ptr)
{
	return ((size_t *)ptr)[-1];
}

void *mallocw(size_t siz)
{
	size_t *ptr;
	assert(siz);
	ptr = (size_t *)malloc(siz += sizeof(size_t));
	_heap('+', siz);
	ptr[0] = siz;
	return &ptr[1];
}

void *callocw(size_t num, size_t siz)
{
	size_t *ptr;
	assert(siz && (size_t)-1/num);
	ptr = (size_t *)mallocw(num * siz);
	return ptr;
}

void *realloc(void *ptr, size_t siz)
{
	size_t *ret, psiz = sizeofw(ptr);
	assert(siz > psiz);
	ret = mallocw(siz);
	while (--psiz > 0) ret[psiz] = ((size_t *)ptr)[psiz];
	freew(ptr);
	return ret;
}

void freew(void *ptr)
{
	_heap('-', ((size_t *)ptr)[-1]);
	free((size_t *)ptr-1);
}

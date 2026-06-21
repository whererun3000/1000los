#include "std.h"

void *memcpy(void *dst, const void *src, size_t n)
{
	char *d = dst;
	const char *s = src;

	for (size_t i = 0; i < n; i++)
		*d++ = *s++;

	return dst;
}

void *memset(void *buf, char c, size_t n)
{
	char *p = buf;

	for (size_t i = 0; i < n; i++)
		*p++ = c;

	return buf;
}

char *strcpy(char *dst, const char *src)
{
	char *d = dst;

	while (*src)
		*d++ = *src++;
	*d = '\0';

	return dst;
}

int strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2) {
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}

	return *s1 - *s2;
}

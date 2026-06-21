#pragma once

#define va_list __builtin_va_list
#define va_start __builtin_va_start
#define va_end __builtin_va_end
#define va_arg __builtin_va_arg

#define offsetof __builtin_offsetof
#define align_up __builtin_align_up
#define is_aligned __builtin_is_aligned

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0

typedef int bool;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef uint size_t;

void putc(char c);
void puts(const char *s);
void printf(const char *fmt, ...);
void vprinf(const char *fmt, va_list);

void *memset(void *buf, char c, size_t n);
void *memcpy(void *dst, const void *src, size_t n);

int strcmp(const char *s1, const char *s2);
char *strcpy(char *s1, const char *s2);

#define panic(fmt, ...)                                               \
	do {                                                          \
		printf("panic: %s:%d: " fmt "\n", __FILE__, __LINE__, \
		       ##__VA_ARGS__);                                \
		while (1)                                             \
			;                                             \
	} while (0)

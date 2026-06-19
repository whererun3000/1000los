#include "std.h"
#include "type.h"

extern char __bss[], __bss_end[], __stack_top[];

void *memset(void *buf, char c, size_t n)
{
	uint8 *p = (uint8 *)buf;
	while (n--)
		*p++ = c;
	return buf;
}

void kernel_main(void)
{
	const char *s = "\n\nHello World!\n";
	for (int i = 0; s[i] != '\0'; i++)
		putchar(s[i]);

	for (;;)
		;
}

__attribute__((section(".text.boot"))) __attribute__((naked)) void boot(void)
{
	__asm__ __volatile__("mv sp, %[stack_top]\n"
			     "j kernel_main\n"
			     :
			     : [stack_top] "r"(__stack_top));
}

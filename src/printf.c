#include "std.h"

static const char digits[] = "0123456789abcdef";

static void reverse_str(char *s, size_t n)
{
	for (int i = 0, j = n - 1; i < j; i++, j--) {
		char c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

static char *format_int(long num, char *buf)
{
	int l = 0;
	long n = num < 0 ? -num : num;

	do {
		buf[l++] = digits[n % 10];
	} while ((n /= 10) > 0);

	if (num < 0)
		buf[l++] = '-';

	reverse_str(buf, l);
	buf[l] = '\0';

	return buf;
}

static char *format_uint(ulong num, int base, char *buf)
{
	int l = 0;
	ulong n = num;

	do {
		buf[l++] = digits[n % base];
	} while ((n /= base));

	reverse_str(buf, l);
	buf[l] = '\0';

	return buf;
}

static char *format_ptr(ulong ptr, char *buf)
{
	buf[0] = '0';
	buf[1] = 'x';
	format_uint(ptr, 16, buf + 2);

	return buf;
}

void vprintf(const char *fmt, va_list ap)
{
	char buf[20];
	char c0, c1, c2;

	for (int i = 0; fmt[i] != '\0'; i++) {
		switch (c0 = fmt[i]) {
		case '%':
			switch (c1 = fmt[++i]) {
			case 'd':
				puts(format_int(va_arg(ap, int), buf));
				break;
			case 'u':
				puts(format_int(va_arg(ap, uint), buf));
				break;
			case 'l':
				switch (c2 = fmt[++i]) {
				case 'd':
					puts(format_int(va_arg(ap, long), buf));
					break;
				case 'u':
					puts(format_uint(va_arg(ap, ulong), 10,
							 buf));
					break;
				default:
					putc(c0);
					putc(c1);
					putc(c2);
					break;
				}

				break;
			case 's':
				puts(va_arg(ap, const char *));
				break;
			case 'x':
				puts(format_uint(va_arg(ap, uint), 16, buf));
				break;
			case 'p':
				puts(format_ptr(va_arg(ap, ulong), buf));
				break;
			case '%':
				putc(c1);
				break;
			default:
				putc(c0);
				putc(c1);
				break;
			}

			break;
		default:
			putc(c0);
			break;
		}
	}
}

void printf(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
}

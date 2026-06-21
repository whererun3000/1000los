#pragma once

struct sbiret {
	long error;
	long value;
};

#define read_csr(reg)                                                 \
	({                                                            \
		ulong __tmp;                                          \
		__asm__ __volatile__("csrr %0, " #reg : "=r"(__tmp)); \
		__tmp;                                                \
	})

#define write_csr(reg, value)                                           \
	do {                                                            \
		ulong __tmp = (value);                                  \
		__asm__ __volatile__("csrw " #reg ", %0" ::"r"(__tmp)); \
	} while (0)

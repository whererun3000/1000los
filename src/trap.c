#include "sbi.h"
#include "std.h"

#define store(rs, mem)

struct trap_frame {
	ulong ra;
	ulong gp;
	ulong tp;
	ulong t0;
	ulong t1;
	ulong t2;
	ulong t3;
	ulong t4;
	ulong t5;
	ulong t6;
	ulong a0;
	ulong a1;
	ulong a2;
	ulong a3;
	ulong a4;
	ulong a5;
	ulong a6;
	ulong a7;
	ulong s0;
	ulong s1;
	ulong s2;
	ulong s3;
	ulong s4;
	ulong s5;
	ulong s6;
	ulong s7;
	ulong s8;
	ulong s9;
	ulong s10;
	ulong s11;
	ulong sp;
} __attribute__((packed));

__attribute__((naked)) __attribute__((aligned(4))) void kernel_trap(void)
{
	__asm__ __volatile__("csrw sscratch, sp\n"
			     "addi sp, sp, -4 * 31\n"

			     "sw ra,  %[size] * 0(sp)\n"
			     "sw gp,  %[size] * 1(sp)\n"
			     "sw tp,  %[size] * 2(sp)\n"
			     "sw t0,  %[size] * 3(sp)\n"
			     "sw t1,  %[size] * 4(sp)\n"
			     "sw t2,  %[size] * 5(sp)\n"
			     "sw t3,  %[size] * 6(sp)\n"
			     "sw t4,  %[size] * 7(sp)\n"
			     "sw t5,  %[size] * 8(sp)\n"
			     "sw t6,  %[size] * 9(sp)\n"
			     "sw a0,  %[size] * 10(sp)\n"
			     "sw a1,  %[size] * 11(sp)\n"
			     "sw a2,  %[size] * 12(sp)\n"
			     "sw a3,  %[size] * 13(sp)\n"
			     "sw a4,  %[size] * 14(sp)\n"
			     "sw a5,  %[size] * 15(sp)\n"
			     "sw a6,  %[size] * 16(sp)\n"
			     "sw a7,  %[size] * 17(sp)\n"
			     "sw s0,  %[size] * 18(sp)\n"
			     "sw s1,  %[size] * 19(sp)\n"
			     "sw s2,  %[size] * 20(sp)\n"
			     "sw s3,  %[size] * 21(sp)\n"
			     "sw s4,  %[size] * 22(sp)\n"
			     "sw s5,  %[size] * 23(sp)\n"
			     "sw s6,  %[size] * 24(sp)\n"
			     "sw s7,  %[size] * 25(sp)\n"
			     "sw s8,  %[size] * 26(sp)\n"
			     "sw s9,  %[size] * 27(sp)\n"
			     "sw s10, %[size] * 28(sp)\n"
			     "sw s11, %[size] * 29(sp)\n"

			     "csrr a0, sscratch\n"
			     "sw a0, %[size] * 30(sp)\n"

			     "mv a0, sp\n"
			     "call handle_trap\n"

			     "lw ra,  %[size] * 0(sp)\n"
			     "lw gp,  %[size] * 1(sp)\n"
			     "lw tp,  %[size] * 2(sp)\n"
			     "lw t0,  %[size] * 3(sp)\n"
			     "lw t1,  %[size] * 4(sp)\n"
			     "lw t2,  %[size] * 5(sp)\n"
			     "lw t3,  %[size] * 6(sp)\n"
			     "lw t4,  %[size] * 7(sp)\n"
			     "lw t5,  %[size] * 8(sp)\n"
			     "lw t6,  %[size] * 9(sp)\n"
			     "lw a0,  %[size] * 10(sp)\n"
			     "lw a1,  %[size] * 11(sp)\n"
			     "lw a2,  %[size] * 12(sp)\n"
			     "lw a3,  %[size] * 13(sp)\n"
			     "lw a4,  %[size] * 14(sp)\n"
			     "lw a5,  %[size] * 15(sp)\n"
			     "lw a6,  %[size] * 16(sp)\n"
			     "lw a7,  %[size] * 17(sp)\n"
			     "lw s0,  %[size] * 18(sp)\n"
			     "lw s1,  %[size] * 19(sp)\n"
			     "lw s2,  %[size] * 20(sp)\n"
			     "lw s3,  %[size] * 21(sp)\n"
			     "lw s4,  %[size] * 22(sp)\n"
			     "lw s5,  %[size] * 23(sp)\n"
			     "lw s6,  %[size] * 24(sp)\n"
			     "lw s7,  %[size] * 25(sp)\n"
			     "lw s8,  %[size] * 26(sp)\n"
			     "lw s9,  %[size] * 27(sp)\n"
			     "lw s10, %[size] * 28(sp)\n"
			     "lw s11, %[size] * 29(sp)\n"
			     "lw sp,  %[size] * 30(sp)\n"

			     "sret\n"
			     :
			     : [size] "i"(sizeof(long)));
}

void handle_trap(struct trap_frame *frame)
{
	ulong epc = read_csr(sepc);
	ulong val = read_csr(stval);
	ulong cause = read_csr(scause);

	panic("unexpected trap scause=%x, stval=%x, sepc=%p\n", cause, val,
	      epc);
}

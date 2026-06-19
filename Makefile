CC=clang
CFLAGS=-I./include -std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fuse-ld=lld -fno-stack-protector -ffreestanding -fno-builtin -nostdlib

QEMU=qemu-system-riscv32
QEMUOPTS=-machine virt -bios default -nographic -serial mon:stdio --no-reboot

SRC_DIR=src

BUILD_DIR=build
KERNEL_ELF=$(BUILD_DIR)/kernel.elf
KERNEL_MAP=$(BUILD_DIR)/kernel.map

run: $(KERNEL_ELF)
	$(QEMU) $(QEMUOPTS) -kernel $<

$(KERNEL_ELF): $(SRC_DIR)/*.c
	$(CC) $(CFLAGS) -Wl,-Tkernel.ld,-Map=$(KERNEL_MAP) -o $@ $^

.PHONY: clean

clean:
	rm -f $(KERNEL_ELF) $(KERNEL_MAP)

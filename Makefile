C_FILES = $(wildcard *.c)
ASM_FILES = $(wildcard *.S)

OBJ_FILES = $(C_FILES:.c=.o)
OBJ_FILES += $(ASM_FILES:.S=.o)

LLVMPATH = /opt/homebrew/opt/llvm
CLANGFLAGS = -target aarch64v8-unknown-none-elf -Wall -O2 -ffreestanding -nostdlib -mcpu=cortex-a72+nosimd


all: clean kernel8.img

%.o: %.S
	$(LLVMPATH)/bin/clang $(CLANGFLAGS) -c $< -o $@

%.o: %.c
	$(LLVMPATH)/bin/clang $(CLANGFLAGS) -c $< -o $@

kernel8.img: link.ld $(OBJ_FILES)
	$(LLVMPATH)/bin/ld.lld -m aarch64elf -T link.ld -o kernel8.elf $(OBJ_FILES)
	$(LLVMPATH)/bin/llvm-objcopy -O binary kernel8.elf kernel8.img

clean:
	/bin/rm kernel8.elf *.o *.img > /dev/null 2> /dev/null || true
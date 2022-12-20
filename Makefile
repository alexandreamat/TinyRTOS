LLVMPATH = /opt/homebrew/opt/llvm
CLANGFLAGS = -target aarch64v8-unknown-none-elf -Wall -O2 -ffreestanding -nostdlib -mcpu=cortex-a72+nosimd -Iinclude 

BUILD_DIR = build
SRC_DIR = src

all: clean kernel8.img

clean:
	rm -rf $(BUILD_DIR) *.img 

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	mkdir -p $(@D)
	$(LLVMPATH)/bin/clang $(CLANGFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(LLVMPATH)/bin/clang $(CLANGFLAGS) -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)

OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)

kernel8.img: $(SRC_DIR)/link.ld $(OBJ_FILES)
	$(LLVMPATH)/bin/ld.lld -m aarch64elf -T $(SRC_DIR)/link.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(LLVMPATH)/bin/llvm-objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

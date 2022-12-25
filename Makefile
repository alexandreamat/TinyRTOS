LLVMPATH = /opt/homebrew/opt/llvm
CLANGFLAGS = -target aarch64v8-unknown-none-elf -Wall -O2 -ffreestanding -nostdlib -mcpu=cortex-a72+nosimd -Iinclude 

BUILD_DIR = build
SRC_DIR = src
SD_DIR = /Volumes/boot

all: clean kernel8.img deploy eject

clean:
	rm -rf $(BUILD_DIR) *.img 

$(BUILD_DIR)/%.S.o: $(SRC_DIR)/%.S
	mkdir -p $(@D)
	$(LLVMPATH)/bin/clang $(CLANGFLAGS) -c $< -o $@

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(LLVMPATH)/bin/clang $(CLANGFLAGS) -c $< -o $@

C_FILES = $(shell find $(SRC_DIR) -type f -name '*.c')
ASM_FILES = $(shell find $(SRC_DIR) -type f -name '*.S')

OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.S.o)

kernel8.img: $(SRC_DIR)/link.ld $(OBJ_FILES)
	$(LLVMPATH)/bin/ld.lld -m aarch64elf -T $(SRC_DIR)/link.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(LLVMPATH)/bin/llvm-objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

deploy:
	cp kernel8.img $(SD_DIR)/
	cp config.txt $(SD_DIR)/

eject:
	diskutil unmountDisk /dev/disk4

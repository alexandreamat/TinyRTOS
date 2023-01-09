TARGET := aarch64-none-elf
TOOLCHAIN_DIR := /Applications/ArmGNUToolchain/12.2.rel1/$(TARGET)

CC := $(TOOLCHAIN_DIR)/bin/$(TARGET)-gcc
LD := $(TOOLCHAIN_DIR)/bin/$(TARGET)-ld
OBJCOPY := $(TOOLCHAIN_DIR)/bin/$(TARGET)-objcopy

CFLAGS = -nostartfiles -Wall -O2 -mcpu=cortex-a72+simd+crypto+crc+fp -Iinclude
LDFLAGS = -L$(TOOLCHAIN_DIR)/$(TARGET)/lib -m aarch64elf -T $(SRC_DIR)/link.ld

BUILD_DIR := build
SRC_DIR := src
SD_DIR := /Volumes/boot

all: clean kernel8.img

clean:
	rm -rf $(BUILD_DIR) *.img 

$(BUILD_DIR)/%.S.o: $(SRC_DIR)/%.S
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

C_FILES = $(shell find $(SRC_DIR) -type f -name '*.c')
ASM_FILES = $(shell find $(SRC_DIR) -type f -name '*.S')

OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.S.o)

kernel8.img: $(SRC_DIR)/link.ld $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)  -lc -lnosys -lm
	$(OBJCOPY) -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

deploy:
	cp kernel8.img $(SD_DIR)/
	cp config.txt $(SD_DIR)/

eject:
	diskutil unmountDisk /dev/disk4

.PHONY: clean deploy eject
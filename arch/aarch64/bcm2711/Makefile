ARCH = aarch64
TOOLCHAIN_PREFIX = $(ARCH)-none-elf
TOOLCHAIN_DIR = /Applications/ArmGNUToolchain/12.2.rel1/$(TARGET)

CFLAGS += -nostartfiles -mcpu=cortex-a72+simd+crypto+crc+fp -DBCM2177
LDFLAGS += -L$(TOOLCHAIN_DIR)/$(TARGET)/lib -m aarch64elf -T $(SRC_DIR)/link.ld

SD_DIR := /Volumes/boot

all: clean kernel8.img

deploy:
	cp kernel8.img $(SD_DIR)/
	cp config.txt $(SD_DIR)/
	diskutil unmountDisk /dev/disk4
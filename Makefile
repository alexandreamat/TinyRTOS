# CC = $(TOOLCHAIN_DIR)/bin/$(TARGET)-gcc
CC = avr-gcc
LD = $(TOOLCHAIN_DIR)/bin/$(TARGET)-ld
OBJCOPY = $(TOOLCHAIN_DIR)/bin/$(TARGET)-objcopy

SRC_DIR := src
BUILD_DIR := build
DRIVER_SRC_DIR := drivers/$(PLATFORM)/src
DRIVER_BUILD_DIR := $(BUILD_DIR)/$(PLATFORM)

CFLAGS := -Wall -Werror -O2 -Iinclude -Idrivers/$(PLATFORM)/include
LDFLAGS := -lc

C_FILES = $(shell find $(SRC_DIR) -type f -name '*.c')
DRIVER_C_FILES = $(shell find $(DRIVER_SRC_DIR) -type f -name '*.c')
# ASM_FILES = $(shell find $(SRC_DIR) -type f -name '*.S')

OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.c.o)
DRIVER_OBJ_FILES = $(DRIVER_C_FILES:$(DRIVER_SRC_DIR)/%.c=$(DRIVER_BUILD_DIR)/%.c.o)

ifeq ($(PLATFORM), bcm2177)

TARGET := aarch64-none-elf
TOOLCHAIN_DIR := /Applications/ArmGNUToolchain/12.2.rel1/$(TARGET)

CFLAGS += -nostartfiles -mcpu=cortex-a72+simd+crypto+crc+fp -DBCM2177
LDFLAGS += -L$(TOOLCHAIN_DIR)/$(TARGET)/lib -m aarch64elf -T $(SRC_DIR)/link.ld

SD_DIR := /Volumes/boot

all: clean kernel8.img

deploy:
	cp kernel8.img $(SD_DIR)/
	cp config.txt $(SD_DIR)/
	diskutil unmountDisk /dev/disk4

else ifeq ($(PLATFORM), avr)

TARGET := avr
DEVICE := atmega328p
F_CPU := 16000000
TOOLCHAIN_DIR := /opt/avr8-gnu-toolchain-darwin_x86_64

CFLAGS += -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) -DAVR

all: clean $(BUILD_DIR)/kernel.hex

deploy: $(BUILD_DIR)/kernel.hex
	avrdude -p $(DEVICE) -c arduino -P $(PORT) -b 115200 -U flash:w:$<

endif

# $(BUILD_DIR)/%.o: $(SRC_DIR)/%
# 	mkdir -p $(@D)
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(DRIVER_BUILD_DIR)/%.o: $(DRIVER_SRC_DIR)/%
# 	mkdir -p $(@D)
# 	$(CC) $(CFLAGS) -c $< -o $@

# %.elf: $(OBJ_FILES) $(DRIVER_OBJ_FILES)
# 	@echo $(OBJ_FILES)
# 	@echo $(DRIVER_OBJ_FILES)
# 	@echo $@
# 	$(LD) $(LDFLAGS) -o $@ $^ 
# # -lc -lnosys -lm

%.elf: $(C_FILES) $(DRIVER_C_FILES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

%.img: %.elf
	$(OBJCOPY) -O binary $< $@

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

clean:
	rm -fr $(BUILD_DIR)

test:
	@echo $(DRIVER_OBJ_FILES)

.PHONY: all deploy clean test


CC = $(TOOLCHAIN_PREFIX)-gcc
LD = $(TOOLCHAIN_PREFIX)-ld
OBJCOPY = $(TOOLCHAIN_PREFIX)-objcopy

SRC_DIR = src
BUILD_DIR = build
TARGET_ARCH_DIR = arch/$(TARGET_ARCH)
TARGET_ARCH_SRC_DIR = arch/$(TARGET_ARCH)/src
TARGET_ARCH_BUILD_DIR = $(BUILD_DIR)/$(TARGET_ARCH)

CFLAGS = -Wall -Wextra -Werror -O2 -Iinclude -I$(TARGET_ARCH_DIR)/include
LDFLAGS = -lc

C_FILES = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.c.o)

TARGET_ARCH_C_FILES = $(shell find $(TARGET_ARCH_SRC_DIR) -type f -name '*.c')
TARGET_ARCH_ASM_FILES = $(shell find $(TARGET_ARCH_SRC_DIR) -type f -name '*.S')

TARGET_ARCH_OBJ_FILES = $(TARGET_ARCH_C_FILES:$(TARGET_ARCH_SRC_DIR)/%.c=$(TARGET_ARCH_BUILD_DIR)/%.c.o)

include arch/$(TARGET_ARCH)/Makefile

%.elf: $(C_FILES) $(TARGET_ARCH_C_FILES)
	mkdir -p $(TARGET_ARCH_BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

%.img: %.elf
	$(OBJCOPY) -O binary $< $@

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

clean:
	rm -fr $(BUILD_DIR)

.PHONY: all deploy clean


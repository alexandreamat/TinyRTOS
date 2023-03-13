ARCH = avr
TOOLCHAIN_PREFIX = $(ARCH)
DEVICE = atmega328p
F_CPU = 16000000

CFLAGS += -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) -DAVR

ifeq ($(DEBUG), 1)
	AVR_STUB_SRC_DIR = $(TARGET_ARCH_DIR)/../avr_debug/avr8-stub
	C_FILES += $(wildcard $(AVR_STUB_SRC_DIR)/*.c)
    CFLAGS += -I$(AVR_STUB_SRC_DIR)
endif

all: $(TARGET_ARCH_BUILD_DIR)/kernel.hex

upload: $(TARGET_ARCH_BUILD_DIR)/kernel.hex
	avrdude -p $(DEVICE) -c arduino -P $(PORT) -b 115200 -U flash:w:$<

display:
	cat $(PORT)

ARCH = avr
TOOLCHAIN_PREFIX = $(ARCH)
DEVICE = atmega328p
F_CPU = 16000000
PORT = /dev/cu.usbmodem*

CFLAGS += -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) -DAVR

ifeq ($(DEBUG), 1)
	AVR_STUB_SRC_DIR = $(TARGET_ARCH_DIR)/../avr_debug/avr8-stub
	C_FILES += $(wildcard $(AVR_STUB_SRC_DIR)/*.c)
    CFLAGS += -I$(AVR_STUB_SRC_DIR)
endif

all: $(TARGET_ARCH_BUILD_DIR)/kernel$(DEBUG).hex

%.stamp: %
	avrdude -p $(DEVICE) -c arduino -P $(PORT) -b 115200 -U flash:w:$<
	touch $@

upload: $(TARGET_ARCH_BUILD_DIR)/kernel$(DEBUG).hex.stamp

display:
	cat $(PORT)

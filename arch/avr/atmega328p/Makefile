ARCH = avr
TOOLCHAIN_PREFIX = $(ARCH)
DEVICE = atmega328p
F_CPU = 16000000

CFLAGS += -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) -DAVR

all: clean $(TARGET_ARCH_BUILD_DIR)/kernel.hex

download: $(TARGET_ARCH_BUILD_DIR)/kernel.hex
	avrdude -p $(DEVICE) -c arduino -P $(PORT) -b 115200 -U flash:w:$<

display:
	cat $(PORT)

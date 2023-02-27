#include "misc.h"

#include "peripherals/gpio.h"

void mmio_write(long int reg, unsigned int val) {
  *(volatile unsigned int *)reg = val;
}

unsigned int mmio_read(long int reg) { return *(volatile unsigned int *)reg; }
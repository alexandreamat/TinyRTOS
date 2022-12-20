#include "gpio.h"

#include "gpio_registers.h"
#include "mmio.h"

static int gpio_call(unsigned int pin, unsigned int value, unsigned int base,
                     unsigned int field_width) {
  unsigned int field_mask = (1 << field_width) - 1;

  if (value > field_mask) return -1;

  unsigned int fields_count = 32 / field_width;
  unsigned int reg = base + ((pin / fields_count) * 4);
  unsigned int shift = (pin % fields_count) * field_width;

  unsigned int curval = mmio_read(reg);
  curval &= ~(field_mask << shift);
  curval |= value << shift;
  mmio_write(reg, curval);

  return 0;
}

int gpio_select_function(unsigned int pin, gpfsel_func_t func) {
  return gpio_call(pin, func, GPFSEL0, 3);
}

int gpio_set(unsigned int pin) { return gpio_call(pin, 1, GPSET0, 1); }

int gpio_clear(unsigned int pin) { return gpio_call(pin, 1, GPCLR0, 1); }

int gpio_pull(unsigned int pin, unsigned int value) {
  return gpio_call(pin, value, GPIO_PUP_PDN_CNTRL_REG0, 2);
}

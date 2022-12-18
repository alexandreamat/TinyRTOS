#include "auxiliaries.h"
#include "gpio.h"
#include "misc.h"

void main(void) {
  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);

  gpio_set(42);
  delay(150);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(150);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(150);
  gpio_clear(42);
  delay(50);

  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);

  uart_init();
  uart_write("Hello world!\n");

  gpio_select_function(42, GPFSEL_FUNC_OUTPUT);
  while (1) {
    gpio_set(42);
    delay(1000);
    gpio_clear(42);
    delay(1000);
  }
}

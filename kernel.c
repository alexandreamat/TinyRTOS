#include "gpio.h"
#include "misc.h"

int main() {
  gpio_select_function(42, GPFSEL_FUNC_OUTPUT);
  while (1) {
    gpio_set(42);
    delay(1000);
    gpio_clear(42);
    delay(1000);
  }
}

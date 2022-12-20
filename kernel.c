#include "auxiliaries.h"
#include "gpio.h"
#include "misc.h"
#include "printf.h"

void putc(void* p, char c) { uart_transmit_char(c); }

extern int get_CurrentEL(void);

void main(void) {
  sos();
  uart_init();
  init_printf(0, putc);
  printf("Hello world!\n");

  int el = get_CurrentEL();
  printf("Exception level: %d\n", el);

  gpio_select_function(42, GPFSEL_FUNC_OUTPUT);
  while (1) {
    gpio_set(42);
    delay(1000);
    gpio_clear(42);
    delay(1000);
  }
}

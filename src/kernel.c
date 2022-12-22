#include "auxiliaries.h"
#include "exceptions.h"
#include "gpio.h"
#include "misc.h"
#include "morse.h"
#include "printf.h"

void putc(void* p, char c) { uart_putc(c); }

extern int get_CurrentEL(void);

void main(void) {
  exceptions_init();
  exceptions_unmask_irq();

  morse_send_text("SOS");

  uart_init();
  init_printf(0, putc);
  printf("Hello world!\n");

  int el = get_CurrentEL();
  printf("Exception level: %d\n", el);
  // exceptions_call_supervisor();

  gpio_select_function(42, GPFSEL_FUNC_OUTPUT);
  while (1) {
    gpio_set(42);
    delay(1000);
    gpio_clear(42);
    delay(1000);
  }
}

#include "exceptions/exceptions.h"
#include "misc.h"
#include "morse.h"
#include "peripherals/auxiliaries/auxiliaries.h"
#include "peripherals/auxiliaries/mini_uart.h"
#include "peripherals/gpio.h"
#include "printf.h"

void putc(void* p, char c) { mini_uart_putc(c); }

#define PRINTREG(reg) (printf("%16s = 0x%08X\n", #reg, mmio_read(reg)))

void main(void) {
  morse_send_text("SOS");
  mini_uart_init();
  init_printf(0, putc);

  exceptions_init_vector_table();
  exceptions_clear_irq_mask_bits();

  printf("\nTinyRTOS Initialising...\n");

  printf("Exception level: %d\n", get_CurrentEL());

  while (1) {
    gpio_set(ACT_CLK);
    delay(1000);
    gpio_clear(ACT_CLK);
    delay(1000);
  }
}

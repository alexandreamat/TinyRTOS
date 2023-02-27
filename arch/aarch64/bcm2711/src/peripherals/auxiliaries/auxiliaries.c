#include "peripherals/auxiliaries/auxiliaries.h"

#include "peripherals/auxiliaries/mini_uart.h"

void auxiliaries_isr(void) {
  if (AUX_IRQ->mini_uart_irq) mini_uart_isr();
}

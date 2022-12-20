#include "auxiliaries.h"

#include "auxiliaries_registers.h"
#include "gpio.h"
#include "misc.h"
#include "mmio.h"

#define AUX_MU_BAUD(baudrate) ((SYS_CLOCK_FREQ / (baudrate * 8)) - 1)

static unsigned int uart_is_transmitter_empty();

void uart_init() {
  mmio_write(AUX_ENABLES, 1);  // enable UART1
  mmio_write(AUX_MU_IER_REG, 0);
  mmio_write(AUX_MU_CNTL_REG, 0);
  mmio_write(AUX_MU_LCR_REG, 3);  // 8 bits // not 1?
  mmio_write(AUX_MU_MCR_REG, 0);
  mmio_write(AUX_MU_IER_REG, 0);
  mmio_write(AUX_MU_IIR_REG, 0xC6);  // disable interrupts
  mmio_write(AUX_MU_BAUD_REG, AUX_MU_BAUD(9600));
  gpio_select_function(14, GPFSEL_FUNC_ALT5);
  gpio_select_function(15, GPFSEL_FUNC_ALT5);
  mmio_write(AUX_MU_CNTL_REG, 3);  // enable RX/TX
}

void uart_transmit_char(char c) {
  while (!uart_is_transmitter_empty()) {
  }
  mmio_write(AUX_MU_IO_REG, (unsigned int)c);
}

static unsigned int uart_is_transmitter_empty() {
  return mmio_read(AUX_MU_LSR_REG) & 0x20;
}
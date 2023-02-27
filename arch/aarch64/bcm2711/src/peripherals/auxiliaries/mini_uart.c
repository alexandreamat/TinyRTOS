#include "peripherals/auxiliaries/mini_uart.h"

#include "misc.h"
#include "peripherals/auxiliaries/auxiliaries.h"
#include "peripherals/gic_400.h"
#include "peripherals/gpio.h"
#include "peripherals/videocore.h"
#include "utils/morse.h"

#define AUX_MU_BAUD(baudrate) ((SYS_CLOCK_FREQ / (baudrate * 8)) - 1)

static void mini_uart_on_rx(void);
static void mini_uart_on_tx(void);

void mini_uart_init() {
  videocore_enable_irq(VC_AUX_IRQ);

  gpio_select_function(TXD0, GPFSEL_FUNC_ALT5);
  gpio_select_function(RXD0, GPFSEL_FUNC_ALT5);

  AUX_ENABLES->mini_uart_enable = true;

  AUX_MU_CNTL_REG->tx_enable = false;
  AUX_MU_CNTL_REG->rx_enable = false;

  AUX_MU_CNTL_REG->enable_rx_auto_flow_ctl_rts = false;
  AUX_MU_CNTL_REG->enable_tx_auto_flow_ctl_cts = false;

  AUX_MU_LCR_REG->data_size_is_8 = true;
  AUX_MU_LCR_REG->magic_bit = true;
  AUX_MU_LCR_REG->break_ = false;
  AUX_MU_LCR_REG->dlab_access = false;

  AUX_MU_IER_REG->enable_rx_interrupt = true;
  AUX_MU_IER_REG->enable_tx_interrupt = true;

  AUX_MU_MCR_REG->rts_is_low = false;

  AUX_MU_IIR_REG->on_write.fifo_clear_rx = true;
  AUX_MU_IIR_REG->on_write.fifo_clear_tx = true;

  AUX_MU_BAUD_REG->baudrate = AUX_MU_BAUD(115200);

  AUX_MU_CNTL_REG->tx_enable = true;
  AUX_MU_CNTL_REG->rx_enable = true;
}

void mini_uart_putc(char c) {
  while (!(AUX_MU_LSR_REG->transmitter_empty)) {
  }
  AUX_MU_IO_REG->tx_data_write = c;
  if ('\n' == c) mini_uart_putc('\r');
}

char mini_uart_getc() {
  while (!AUX_MU_LSR_REG->data_ready) {
  }
  return AUX_MU_IO_REG->rx_data_read;
}

void mini_uart_isr(void) {
  switch (AUX_MU_IIR_REG->on_read.interrupt_id_bits) {
    case UART_INTERRUPT_ID_BIT_RX:
      mini_uart_on_rx();
      break;
    case UART_INTERRUPT_ID_BIT_TX:
      mini_uart_on_tx();
      break;
    default:
      break;
  }
}

static void mini_uart_on_rx(void) {
  while (AUX_MU_LSR_REG->data_ready) mini_uart_putc(mini_uart_getc());
}

static void mini_uart_on_tx(void) {
  gpio_write(GPIO_ACT_LED, true);
  delay(50);
  gpio_write(GPIO_ACT_LED, false);
}
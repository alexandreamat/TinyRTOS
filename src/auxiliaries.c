#include "auxiliaries.h"

#include "auxiliaries_registers.h"
// #include "exceptions_registers.h"
#include <stdbool.h>

#include "gpio.h"
#include "misc.h"
#include "mmio.h"
// #include "morse.h"
// #include "queue.h"

// #define UART_TX_BUF_SIZE (16 * 1024)

#define AUX_MU_BAUD(baudrate) ((SYS_CLOCK_FREQ / (baudrate * 8)) - 1)

// static char g_uart_tx_buf[UART_TX_BUF_SIZE] = {0};
// static queue_t g_uart_tx_queue = {0};

// static void uart_isr(void);
// static void uart_on_tx(void);

void uart_init() {
  // set GPIO
  gpio_select_function(14, GPFSEL_FUNC_ALT5);
  gpio_select_function(15, GPFSEL_FUNC_ALT5);

  // Enable UART1
  AUX_ENABLES->mini_uart_enable = true;

  // Disable Tx/Rx while configuring
  AUX_MU_IER_REG->enable_receive_interrupt = false;
  AUX_MU_IER_REG->enable_transmit_interrupt = false;
  AUX_MU_CNTL_REG->receiver_enable = false;
  AUX_MU_CNTL_REG->transmitter_enable = false;

  // Configure
  AUX_MU_LCR_REG->data_size_is_8 = true;
  AUX_MU_MCR_REG->rts_is_low = false;
  AUX_MU_IIR_REG->on_write.fifo_clear_rx = true;
  AUX_MU_IIR_REG->on_write.fifo_clear_tx = true;
  AUX_MU_BAUD_REG->baudrate = AUX_MU_BAUD(9600);

  // Enable Tx/Rx
  AUX_MU_CNTL_REG->receiver_enable = true;
  AUX_MU_CNTL_REG->transmitter_enable = true;

  // queue_init(&g_uart_tx_queue, g_uart_tx_buf, UART_TX_BUF_SIZE);
  // mmio_write(IRQ0_SET_EN_0, 1 << (VIDEOCORE_IRQ_AUX));
}

void uart_putc(char c) {
  while (!AUX_MU_LSR_REG->transmitter_empty) {
  }
  AUX_MU_IO_REG->transmit_data_write = c;
  // queue_add(&g_uart_tx_queue, c);
}

// void auxiliaries_isr(void) {
//   if (mmio_read(AUX_IRQ) & (1 < 0)) uart_isr();
//   mmio_write(AUX_MU_IER_REG, 0b11);
// }

// static void uart_isr(void) {
//   unsigned int reg_val = (mmio_read(AUX_MU_IIR_REG) & 0b110) >> 1;
//   if (UART_INTERRUPT_ID_BIT_TX == reg_val) uart_on_tx();
// }

// static void uart_on_tx(void) {
//   while (!queue_is_empty(&g_uart_tx_queue) && uart_is_transmitter_empty()) {
//     mmio_write(AUX_MU_IO_REG, (unsigned int)queue_remove(&g_uart_tx_queue));
//   }
// }

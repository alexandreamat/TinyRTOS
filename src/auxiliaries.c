#include "auxiliaries.h"

#include "auxiliaries_registers.h"
// #include "exceptions_registers.h"
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
  // queue_init(&g_uart_tx_queue, g_uart_tx_buf, UART_TX_BUF_SIZE);
  // mmio_write(IRQ0_SET_EN_0, 1 << (VIDEOCORE_IRQ_AUX));
}

void uart_putc(char c) {
  while (!uart_is_transmitter_empty()) {
  }
  mmio_write(AUX_MU_IO_REG, (unsigned int)c);
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

static unsigned int uart_is_transmitter_empty() {
  return mmio_read(AUX_MU_LSR_REG) & 0x20;
}
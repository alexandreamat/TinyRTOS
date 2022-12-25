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
  mini_uart_init();
  init_printf(0, putc);

  // exceptions_init_vector_table();
  // exceptions_clear_irq_mask_bits();
  mini_uart_putc('H');
  mini_uart_putc('E');
  mini_uart_putc('L');
  mini_uart_putc('L');
  mini_uart_putc('O');
  // printf("\nTinyRTOS Initialising...\n");

  printf("Exception level: %d\n", get_CurrentEL());

  while (1) {
    // PRINTREG(IRQ0_PENDING0);
    // // PRINTREG(IRQ0_PENDING1);
    // // PRINTREG(IRQ0_PENDING2);
    // // PRINTREG(IRQ1_PENDING0);
    // // PRINTREG(IRQ1_PENDING1);
    // // PRINTREG(IRQ1_PENDING2);
    // // PRINTREG(IRQ2_PENDING0);
    // // PRINTREG(IRQ2_PENDING1);
    // // PRINTREG(IRQ2_PENDING2);
    // // PRINTREG(IRQ3_PENDING0);
    // // PRINTREG(IRQ3_PENDING1);
    // // PRINTREG(IRQ3_PENDING2);
    // PRINTREG(IRQ_STATUS0);
    // // PRINTREG(IRQ_STATUS1);
    // // PRINTREG(IRQ_STATUS2);
    // PRINTREG(AUX_IRQ);
    // // PRINTREG(AUX_ENABLES);
    // PRINTREG(AUX_MU_IER_REG);
    // PRINTREG(AUX_MU_IIR_REG);
    // // PRINTREG(AUX_MU_LCR_REG);
    // // PRINTREG(AUX_MU_MCR_REG);
    // PRINTREG(AUX_MU_LSR_REG);
    // // PRINTREG(AUX_MU_MSR_REG);
    // // PRINTREG(AUX_MU_SCRATCH);
    // // PRINTREG(AUX_MU_CNTL_REG);
    // PRINTREG(AUX_MU_STAT_REG);
    // // PRINTREG(AUX_MU_BAUD_REG);
    // printf("AUX_MU_IO_REG = '%c'\n", (char)(mmio_read(AUX_MU_IO_REG) &
    // 0xFF));
    // printf("\n");
    delay(3000);
  }
}

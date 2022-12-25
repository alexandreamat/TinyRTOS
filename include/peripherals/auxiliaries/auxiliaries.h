#ifndef __AUXILIARIES_H__
#define __AUXILIARIES_H__

#include <stdbool.h>

#include "peripherals/base.h"

#define AUX_IRQ ((volatile aux_irq_t *const)(AUX_BASE + 0x00))
#define AUX_ENABLES ((volatile aux_enables_t *const)(AUX_BASE + 0x04))

#define AUX_SPI1_CNTL0_REG (AUX_BASE + 0x80)    // SPI 1 Control register 0
#define AUX_SPI1_CNTL1_REG (AUX_BASE + 0x84)    // SPI 1 Control register 1
#define AUX_SPI1_STAT_REG (AUX_BASE + 0x88)     // SPI 1 Status
#define AUX_SPI1_PEEK_REG (AUX_BASE + 0x8C)     // SPI 1 Peek
#define AUX_SPI1_IO_REGA (AUX_BASE + 0xA0)      // SPI 1 Data
#define AUX_SPI1_IO_REGB (AUX_BASE + 0xA4)      // SPI 1 Data
#define AUX_SPI1_IO_REGC (AUX_BASE + 0xA8)      // SPI 1 Data
#define AUX_SPI1_IO_REGD (AUX_BASE + 0xAC)      // SPI 1 Data
#define AUX_SPI1_TXHOLD_REGA (AUX_BASE + 0xB0)  // SPI 1 Extended Data
#define AUX_SPI1_TXHOLD_REGB (AUX_BASE + 0xB4)  // SPI 1 Extended Data
#define AUX_SPI1_TXHOLD_REGC (AUX_BASE + 0xB8)  // SPI 1 Extended Data
#define AUX_SPI1_TXHOLD_REGD (AUX_BASE + 0xBC)  // SPI 1 Extended Data

#define AUX_SPI2_CNTL0_REG (AUX_BASE + 0xC0)    // SPI 2 Control register 0
#define AUX_SPI2_CNTL1_REG (AUX_BASE + 0xC4)    // SPI 2 Control register 1
#define AUX_SPI2_STAT_REG (AUX_BASE + 0xC8)     // SPI 2 Status
#define AUX_SPI2_PEEK_REG (AUX_BASE + 0xCC)     // SPI 2 Peek
#define AUX_SPI2_IO_REGA (AUX_BASE + 0xE0)      // SPI 2 Data
#define AUX_SPI2_IO_REGB (AUX_BASE + 0xE4)      // SPI 2 Data
#define AUX_SPI2_IO_REGC (AUX_BASE + 0xE8)      // SPI 2 Data
#define AUX_SPI2_IO_REGD (AUX_BASE + 0xEC)      // SPI 2 Data
#define AUX_SPI2_TXHOLD_REGA (AUX_BASE + 0xF0)  // SPI 2 Extended Data
#define AUX_SPI2_TXHOLD_REGB (AUX_BASE + 0xF4)  // SPI 2 Extended Data
#define AUX_SPI2_TXHOLD_REGC (AUX_BASE + 0xF8)  // SPI 2 Extended Data
#define AUX_SPI2_TXHOLD_REGD (AUX_BASE + 0xFC)  // SPI 2 Extended Data

typedef struct {
  const bool mini_uart_irq : 1;
  const bool spi_1_irq : 1;
  const bool spi_2_irq : 1;
} aux_irq_t;

typedef struct {
  bool mini_uart_enable : 1;
  bool spi1_enable : 1;
  bool spi2_enable : 1;
} aux_enables_t;

void auxiliaries_isr(void);

#endif  // __AUXILIARIES_H__
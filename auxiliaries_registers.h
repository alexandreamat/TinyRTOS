#ifndef __AUXILIARIES_REGISTERS_H__
#define __AUXILIARIES_REGISTERS_H__

#include "base_registers.h"

#define AUX_IRQ (AUX_BASE + 0x00)  // Auxiliary Interrupt status

#define AUX_ENABLES (AUX_BASE + 0x04)  // Auxiliary enables

#define AUX_MU_IO_REG (AUX_BASE + 0x40)    // Mini UART I/O Data
#define AUX_MU_IER_REG (AUX_BASE + 0x44)   // Mini UART Interrupt Enable
#define AUX_MU_IIR_REG (AUX_BASE + 0x48)   // Mini UART Interrupt Identify
#define AUX_MU_LCR_REG (AUX_BASE + 0x4C)   // Mini UART Line Control
#define AUX_MU_MCR_REG (AUX_BASE + 0x50)   // Mini UART Modem Control
#define AUX_MU_LSR_REG (AUX_BASE + 0x54)   // Mini UART Line Status
#define AUX_MU_MSR_REG (AUX_BASE + 0x58)   // Mini UART Modem Status
#define AUX_MU_SCRATCH (AUX_BASE + 0x5C)   // Mini UART Scratch
#define AUX_MU_CNTL_REG (AUX_BASE + 0x60)  // Mini UART Extra Control
#define AUX_MU_STAT_REG (AUX_BASE + 0x64)  // Mini UART Extra Status
#define AUX_MU_BAUD_REG (AUX_BASE + 0x68)  // Mini UART Baudrate

#define AUX_SPI1_CNTL0_REG (AUX_BASE + 0x80)    // SPI 1 Control register 0
#define AUX_SPI1_CNTL1_REG (AUX_BASE + 0x84)    // SPI 1 Control register 1
#define AUX_SPI1_STAT_REG (AUX_BASE + 0x88)     // SPI 1 Status
#define AUX_SPI1_PEEK_REG (AUX_BASE + 0x8C)     // SPI 1 Peek
#define AUX_SPI1_IO_REGa (AUX_BASE + 0xA0)      // SPI 1 Data
#define AUX_SPI1_IO_REGb (AUX_BASE + 0xA4)      // SPI 1 Data
#define AUX_SPI1_IO_REGc (AUX_BASE + 0xA8)      // SPI 1 Data
#define AUX_SPI1_IO_REGd (AUX_BASE + 0xAC)      // SPI 1 Data
#define AUX_SPI1_TXHOLD_REGa (AUX_BASE + 0xB0)  // SPI 1 Extended Data
#define AUX_SPI1_TXHOLD_REGb (AUX_BASE + 0xB4)  // SPI 1 Extended Data
#define AUX_SPI1_TXHOLD_REGc (AUX_BASE + 0xB8)  // SPI 1 Extended Data
#define AUX_SPI1_TXHOLD_REGd (AUX_BASE + 0xBC)  // SPI 1 Extended Data

#define AUX_SPI2_CNTL0_REG (AUX_BASE + 0xC0)    // SPI 2 Control register 0
#define AUX_SPI2_CNTL1_REG (AUX_BASE + 0xC4)    // SPI 2 Control register 1
#define AUX_SPI2_STAT_REG (AUX_BASE + 0xC8)     // SPI 2 Status
#define AUX_SPI2_PEEK_REG (AUX_BASE + 0xCC)     // SPI 2 Peek
#define AUX_SPI2_IO_REGa (AUX_BASE + 0xE0)      // SPI 2 Data
#define AUX_SPI2_IO_REGb (AUX_BASE + 0xE4)      // SPI 2 Data
#define AUX_SPI2_IO_REGc (AUX_BASE + 0xE8)      // SPI 2 Data
#define AUX_SPI2_IO_REGd (AUX_BASE + 0xEC)      // SPI 2 Data
#define AUX_SPI2_TXHOLD_REGa (AUX_BASE + 0xF0)  // SPI 2 Extended Data
#define AUX_SPI2_TXHOLD_REGb (AUX_BASE + 0xF4)  // SPI 2 Extended Data
#define AUX_SPI2_TXHOLD_REGc (AUX_BASE + 0xF8)  // SPI 2 Extended Data
#define AUX_SPI2_TXHOLD_REGd (AUX_BASE + 0xFC)  // SPI 2 Extended Data

typedef enum {
  UART_INTERRUPT_ID_BIT_NONE = 0b00,  // No interrupts
  UART_INTERRUPT_ID_BIT_TX = 0b01,    // Transmit holding register empty
  UART_INTERRUPT_ID_BIT_RX = 0b10     // Receiver holds valid byte
} uart_interrupt_id_bit_t;

#endif  // __AUXILIARIES_REGISTERS_H__

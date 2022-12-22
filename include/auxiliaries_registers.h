#ifndef __AUXILIARIES_REGISTERS_H__
#define __AUXILIARIES_REGISTERS_H__

#include "base_registers.h"

typedef struct {
  volatile unsigned int mini_uart_irq : 1;  // If set the mini UART has an
                                            // interrupt pending. RO 0x0
  volatile unsigned int
      spi_1_irq : 1;  // If set the SPI1 module has an interrupt pending. RO 0x0
  volatile unsigned int spi_2_irq : 1;  // If set the SPI 2 module has an
                                        // interrupt pending. RO 0x0
} aux_irq_t;

#define AUX_IRQ ((aux_irq_t *)(AUX_BASE + 0x00))  // Auxiliary Interrupt status

typedef struct {
  volatile unsigned int
      mini_uart_enable : 1;  // If set the mini UART is enabled. The UART will
                             // immediately start receiving data, especially if
                             // the UART1_RX line is low. If clear the mini UART
                             // is disabled. That also disables any mini UART
                             // register access
  volatile unsigned int
      spi1_enable : 1;  // If set the SPI 1 module is enabled. If clear the SPI
                        // 1 module is disabled. That also disables any SPI 1
                        // module register access
  volatile unsigned int
      spi2_enable : 1;  // If set the SPI 2 module is enabled. If clear the SPI
                        // 2 module is disabled. That also disables any SPI 2
                        // module register access
} aux_enables_t;

#define AUX_ENABLES ((aux_enables_t *)(AUX_BASE + 0x04))  // Auxiliary enables

typedef union {
  volatile unsigned int
      receive_data_read : 8;  // DLAB=0 Data read is taken from the receive FIFO
                              // (Provided it is not empty) (Only if bit 7 of
                              // the line control register (DLAB bit) is clear)
                              // RO 0x00
  volatile unsigned int
      transmit_data_write : 8;  // DLAB=0 Data written is put in the transmit
                                // FIFO (Provided it is not full) (Only if bit 7
                                // of the line control register (DLAB bit) is
                                // clear) WO 0x00
  volatile unsigned int
      ls_8_bits_baudrate_read_write : 8;  // DLAB=1 Access to the LS 8 bits of
                                          // the 16-bit baudrate register. (Only
                                          // if bit 7 of the line control
                                          // register (DLAB bit) is set) RW 0x00
} aux_mu_io_reg_t;

// Mini UART I/O Data
#define AUX_MU_IO_REG ((aux_mu_io_reg_t *)(AUX_BASE + 0x40))

typedef struct {
  volatile unsigned int
      enable_transmit_interrupt : 1;  // (DLAB=0) If this bit is set the
                                      // interrupt line is asserted whenever the
                                      // transmit FIFO is empty. If this bit is
                                      // clear no transmit interrupts are
                                      // generated. RW 0x0
  volatile unsigned int
      enable_receive_interrupt : 1;  // (DLAB=0) If this bit is set the
                                     // interrupt line is asserted whenever the
                                     // receive FIFO holds at least 1 byte. If
                                     // this bit is clear no receive interrupts
                                     // are generated. RW 0x0
  volatile unsigned int
      ms_8_bits_baudrate_read_write : 8;  // DLAB=1 Access to the MS 8 bits of
                                          // the 16-bit baudrate register. (Only
                                          // if bit 7 of the line control
                                          // register (DLAB bit) is set) RW 0x00
} aux_mu_ier_reg_t;

// Mini UART Interrupt Enable
#define AUX_MU_IER_REG ((aux_mu_ier_reg_t *)(AUX_BASE + 0x44))

typedef enum {
  UART_INTERRUPT_ID_BIT_NONE = 0b00,  // No interrupts
  UART_INTERRUPT_ID_BIT_TX = 0b01,    // Transmit holding register empty
  UART_INTERRUPT_ID_BIT_RX = 0b10     // Receiver holds valid byte
} uart_interrupt_id_bit_t;

typedef union {
  struct {
    volatile unsigned int
        interrupt_pending : 1;  // This bit is clear whenever an interrupt is
                                // pending RO 0x1
    volatile uart_interrupt_id_bit_t
        interrupt_id_bits : 2;  // On read this register shows the interrupt ID
  } on_read;
  struct {
    volatile unsigned int : 1;
    volatile unsigned int fifo_clear_rx : 1;  // Writing with bit 1 set will
                                              // clear the receive FIFO
    volatile unsigned int fifo_clear_tx : 1;  // Writing with bit 2 set will
                                              // clear the transmit FIFO
  } on_write;
} aux_mu_iir_reg_t;

// Mini UART Interrupt Identify
#define AUX_MU_IIR_REG ((aux_mu_iir_reg_t *)(AUX_BASE + 0x48))

typedef struct {
  volatile unsigned int
      data_size_is_8 : 1;  // If clear the UART works in 7-bit mode If set the
                           // UART works in 8-bit mode RW 0x0
  volatile unsigned int : 5;
  volatile unsigned int
      break_ : 1;  // If set high the UART1_TX line is pulled low continuously.
                   // If held for at least 12 bits times that will indicate a
                   // break condition. RW 0x0
  volatile unsigned int
      dlab_access : 1;  // If set the first two Mini UART registers give access
                        // to the Baudrate register. During operation this bit
                        // must be cleared. RW 0x0
} aux_mu_lcr_reg_t;

// Mini UART Line Control
#define AUX_MU_LCR_REG ((aux_mu_lcr_reg_t *)(AUX_BASE + 0x4C))

typedef struct {
  volatile unsigned int : 1;
  volatile unsigned int
      rts_is_low : 1;  // If clear the UART1_RTS line is high If set the
                       // UART1_RTS line is low This bit is ignored if the RTS
                       // is used for auto-flow control. See the Mini UART Extra
                       // Control register description) RW 0x0
} aux_mu_mcr_reg_t;

// Mini UART Modem Control
#define AUX_MU_MCR_REG ((aux_mu_mcr_reg_t *)(AUX_BASE + 0x50))

typedef struct {
  volatile unsigned int data_ready : 1;  // This bit is set if the receive FIFO
                                         // holds at least 1 symbol. RO 0x0
  volatile unsigned int
      receiver_overrun : 1;  // This bit is set if there was a receiver overrun.
                             // That is: one or more characters arrived whilst
                             // the receive FIFO was full. The newly arrived
                             // characters have been discarded. This bit is
                             // cleared each time this register is read. To do a
                             // non- destructive read of this overrun bit use
                             // the Mini UART Extra Status register. RC 0x0
  volatile unsigned int : 3;
  volatile unsigned int
      transmitter_empty : 1;  // This bit is set if the transmit FIFO can accept
                              // at least one byte. RO 0x0
  volatile unsigned int
      transmitter_idle : 1;  // This bit is set if the transmit FIFO is empty
                             // and the transmitter is idle. (Finished shifting
                             // out the last bit). RO 0x1
} aux_mu_lsr_reg_t;

// Mini UART Line Status
#define AUX_MU_LSR_REG ((aux_mu_lsr_reg_t *)(AUX_BASE + 0x54))

#define AUX_MU_MSR_REG (AUX_BASE + 0x58)  // Mini UART Modem Status

#define AUX_MU_SCRATCH (AUX_BASE + 0x5C)  // Mini UART Scratch

typedef enum {
  // De-assert RTS when the receive FIFO has 3 empty spaces left.
  RTS_AUTO_FLOW_LEVEL_3 = 0b00,
  // De-assert RTS when the receive FIFO has 2 empty spaces left.
  RTS_AUTO_FLOW_LEVEL_2 = 0b01,
  // De-assert RTS when the receive FIFO has 1 empty space left.
  RTS_AUTO_FLOW_LEVEL_1 = 0b10,
  // De-assert RTS when the receive FIFO has 4 empty spaces left.
  RTS_AUTO_FLOW_LEVEL_4 = 0b11
} rts_auto_flow_level_t;

typedef struct {
  volatile unsigned int
      receiver_enable : 1;  // If this bit is set the mini UART receiver is
                            // enabled. If this bit is clear the mini UART
                            // receiver is disabled RW 0x1
  volatile unsigned int
      transmitter_enable : 1;  // If this bit is set the mini UART transmitter
                               // is enabled. If this bit is clear the mini UART
                               // transmitter is disabled RW 0x1
  volatile unsigned int
      enable_rx_auto_flow_ctl_rts : 1;  // If this bit is set the RTS line will
                                        // de-assert if the receive FIFO reaches
                                        // its 'auto flow' level. In fact the
                                        // RTS line will behave as an RTR (Ready
                                        // To Receive) line. If this bit is
                                        // clear the RTS line is controlled by
                                        // the AUX_MU_MCR_REG register bit 1. RW
                                        // 0x0
  volatile unsigned int
      enable_tx_auto_flow_ctl_cts : 1;  // If this bit is set the transmitter
                                        // will stop if the CTS line is de-
                                        // asserted. If this bit is clear the
                                        // transmitter will ignore the status of
                                        // the CTS line RW 0x0
  volatile rts_auto_flow_level_t
      rts_auto_flow_level : 2;  // These two bits specify at what receiver FIFO
                                // level the RTS line is de-asserted in
                                // auto-flow mode. RW 0x0
  volatile unsigned int
      cts_assert_level : 1;  // This bit allows one to invert the CTS auto flow
                             // operation polarity. If set the CTS auto flow
                             // assert level is low* If clear the CTS auto flow
                             // assert level is high* RW 0x0
  volatile unsigned int
      rts_assert_level : 1;  // This bit allows one to invert the RTS auto flow
                             // operation polarity. If set the RTS auto flow
                             // assert level is low* If clear the RTS auto flow
                             // assert level is high* RW 0x0
} aux_mu_ctrl_reg_t;

// Mini UART Extra Control
#define AUX_MU_CNTL_REG ((aux_mu_ctrl_reg_t *)(AUX_BASE + 0x60))

typedef struct {
  volatile unsigned int
      symbol_available : 1;  // If this bit is set the mini UART receive FIFO
                             // contains at least 1 symbol If this bit is clear
                             // the mini UART receiver FIFO is empty RO 0x0
  volatile unsigned int
      space_available : 1;  // If this bit is set the mini UART transmitter FIFO
                            // can accept at least one more symbol. If this bit
                            // is clear the mini UART transmitter FIFO is full
                            // RO 0x0
  volatile unsigned int
      receiver_is_idle : 1;  // If this bit is set the receiver is idle. If this
                             // bit is clear the receiver is busy. This bit can
                             // change unless the receiver is disabled RO 0x1
  volatile unsigned int
      transmitter_is_idle : 1;  // If this bit is set the transmitter is idle.
                                // If this bit is clear the transmitter is busy.
                                // RO 0x1
  volatile unsigned int
      receiver_overrun : 1;  // This bit is set if there was a receiver overrun.
                             // That is: one or more characters arrived whilst
                             // the receive FIFO was full. The newly arrived
                             // characters have been discarded. This bit is
                             // cleared each time the AUX_MU_LSR_REG register is
                             // read. RO 0x0
} aux_mu_stat_reg_t;

// Mini UART Extra Status
#define AUX_MU_STAT_REG ((aux_mu_stat_reg_t *)(AUX_BASE + 0x64))

typedef struct {
  volatile unsigned int baudrate : 16;  // mini UART baudrate counter
} aux_mu_baud_reg_t;

// Mini UART Baudrate
#define AUX_MU_BAUD_REG ((aux_mu_baud_reg_t *)(AUX_BASE + 0x68))

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

#endif  // __AUXILIARIES_REGISTERS_H__

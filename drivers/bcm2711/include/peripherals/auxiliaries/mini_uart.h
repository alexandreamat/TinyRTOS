#ifndef __MINI_UART_H__
#define __MINI_UART_H__

#include <stdbool.h>

#define AUX_MU_IO_REG ((volatile aux_mu_io_reg_t *const)(AUX_BASE + 0x40))
#define AUX_MU_IER_REG ((volatile aux_mu_ier_reg_t *const)(AUX_BASE + 0x44))
#define AUX_MU_IIR_REG ((volatile aux_mu_iir_reg_t *const)(AUX_BASE + 0x48))
#define AUX_MU_LCR_REG ((volatile aux_mu_lcr_reg_t *const)(AUX_BASE + 0x4C))
#define AUX_MU_MCR_REG ((volatile aux_mu_mcr_reg_t *const)(AUX_BASE + 0x50))
#define AUX_MU_LSR_REG ((volatile aux_mu_lsr_reg_t *const)(AUX_BASE + 0x54))
#define AUX_MU_MSR_REG (AUX_BASE + 0x58)
#define AUX_MU_SCRATCH (AUX_BASE + 0x5C)
#define AUX_MU_CNTL_REG ((volatile aux_mu_ctrl_reg_t *const)(AUX_BASE + 0x60))
#define AUX_MU_STAT_REG ((volatile aux_mu_stat_reg_t *const)(AUX_BASE + 0x64))
#define AUX_MU_BAUD_REG ((volatile aux_mu_baud_reg_t *const)(AUX_BASE + 0x68))

typedef enum {
  RTS_AUTO_FLOW_LEVEL_3 = 0b00,
  RTS_AUTO_FLOW_LEVEL_2 = 0b01,
  RTS_AUTO_FLOW_LEVEL_1 = 0b10,
  RTS_AUTO_FLOW_LEVEL_4 = 0b11
} rts_auto_flow_level_t;

typedef enum {
  UART_INTERRUPT_ID_BIT_NONE = 0b00,
  UART_INTERRUPT_ID_BIT_TX = 0b01,
  UART_INTERRUPT_ID_BIT_RX = 0b10
} uart_interrupt_id_bit_t;

typedef union {
  const char rx_data_read : 8;
  char tx_data_write : 8;
  unsigned int ls_8_bits_baudrate_read_write : 8;
} aux_mu_io_reg_t;

typedef union {
  bool enable_rx_interrupt : 1;  // In the manual Tx
  bool enable_tx_interrupt : 1;  // In the manual Rx
} aux_mu_ier_reg_t;

typedef union {
  const struct {
    bool interrupt_not_pending : 1;
    uart_interrupt_id_bit_t interrupt_id_bits : 2;
  } on_read;
  struct {
    int : 1;
    bool fifo_clear_rx : 1;
    bool fifo_clear_tx : 1;
  } on_write;
} aux_mu_iir_reg_t;

typedef struct {
  bool data_size_is_8 : 1;
  bool magic_bit : 1;
  int : 4;
  bool break_ : 1;
  bool dlab_access : 1;
} aux_mu_lcr_reg_t;

typedef struct {
  int : 1;
  bool rts_is_low : 1;
} aux_mu_mcr_reg_t;

typedef const struct {
  bool data_ready : 1;
  bool receiver_overrun : 1;
  int : 3;
  bool transmitter_empty : 1;
  bool transmitter_idle : 1;
} aux_mu_lsr_reg_t;

typedef struct {
  bool rx_enable : 1;
  bool tx_enable : 1;
  bool enable_rx_auto_flow_ctl_rts : 1;
  bool enable_tx_auto_flow_ctl_cts : 1;
  rts_auto_flow_level_t rts_auto_flow_level : 2;
  bool cts_assert_level : 1;
  bool rts_assert_level_is_low : 1;
} aux_mu_ctrl_reg_t;

typedef const struct {
  bool symbol_available : 1;
  bool space_available : 1;
  bool receiver_is_idle : 1;
  bool transmitter_is_idle : 1;
  bool receiver_overrun : 1;
} aux_mu_stat_reg_t;

typedef struct {
  unsigned int baudrate : 16;
} aux_mu_baud_reg_t;

void mini_uart_init(void);
void mini_uart_putc(char c);
char mini_uart_getc(void);
void mini_uart_isr(void);

#endif  // __MINI_UART_H__
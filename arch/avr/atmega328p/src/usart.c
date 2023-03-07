#include "usart.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#include "libc/time.h"
#include "utils/queue.h"

/* ====== Preprocessor Definitions ====== */

#define USART_RX_Q_SIZE (127)
#define USART_TX_Q_SIZE (255)
#define USART_UCSZ_8_BIT (3)

/* ====== Static Variables ====== */

static queue_t *g_usart_rx_q = NULL;
static queue_t *g_usart_tx_q = NULL;
static bool usart_tx_int = false;

/* ====== Static Function Declarations ====== */

static inline bool usart_rx_is_ready(void);
static inline bool usart_tx_is_ready(void);
static inline char usart_rx_char(void);
static inline void usart_tx_char(char c);

/* ====== External Function Definitions ====== */

ISR(USART_RX_vect) {
  do {
    queue_char_push(g_usart_rx_q, UDR0);
  } while (usart_rx_is_ready());
}

ISR(USART_TX_vect) {
  if (queue_char_is_empty(g_usart_tx_q)) return;
  usart_tx_char(queue_char_pop(g_usart_tx_q));
}

void usart_init(bool tx_int) {
  usart_tx_int = tx_int;
  g_usart_rx_q = queue_char_create(USART_RX_Q_SIZE);
  g_usart_tx_q = queue_char_create(USART_TX_Q_SIZE);
  UBRR0 = F_CPU / (USART_BAUD * 16UL) - 1;
  UCSR0C = USART_UCSZ_8_BIT << UCSZ00;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (tx_int << TXCIE0);
}

void usart_transmit(char c) {
  if (usart_tx_int)
    if (usart_tx_is_ready()) {
      usart_tx_char(c);
      return;
    }
  queue_char_push(g_usart_tx_q, c);
}

char usart_receive(void) {
  while (queue_char_is_empty(g_usart_rx_q)) continue;
  return queue_char_pop(g_usart_rx_q);
}

void usart_flush(void) {
  while (!queue_char_is_empty(g_usart_tx_q)) {
    while (!usart_tx_is_ready()) continue;
    usart_tx_char(queue_char_pop(g_usart_tx_q));
  }
}

/* ====== Static Function Definitions ====== */

static inline bool usart_rx_is_ready(void) { return UCSR0A & (1 << RXC0); }

static inline bool usart_tx_is_ready(void) { return UCSR0A & (1 << UDRE0); }

static inline char usart_rx_char(void) { return UDR0; }

static inline void usart_tx_char(char c) { UDR0 = c; }

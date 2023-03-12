#ifndef DEBUG

#include "usart.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/atomic.h>

#include "libc/time.h"
#include "utils/queue.h"

/* ====== Preprocessor Definitions ====== */

#define USART_RX_Q_SIZE (127)
#define USART_TX_Q_SIZE (800)
#define USART_UCSZ_8_BIT (3)
#define USART_ATOMIC_TX                                              \
  for (char x = ({                                                   \
         ATOMIC_BLOCK(ATOMIC_RESTORESTATE) UCSR0B &= ~(1 << TXCIE0); \
         1;                                                          \
       });                                                           \
       ({                                                            \
         ATOMIC_BLOCK(ATOMIC_RESTORESTATE) UCSR0B |= (1 << TXCIE0);  \
         x;                                                          \
       });                                                           \
       x = 0)

/* ====== Static Variables ====== */

static queue_t* g_usart_rx_q = NULL;
static queue_t* g_usart_tx_q = NULL;
void (*usart_transmit)(char c) = NULL;

/* ====== Static Function Declarations ====== */

static inline void usart_transmit_buffered(char c);
static inline void usart_transmit_unbuffered(char c);
static inline void usart_on_tx_ready(void);
static inline void usart_on_rx_ready(void);
static inline bool usart_is_tx_ready(void);
static inline bool usart_is_rx_ready(void);
static inline void usart_tx_char(char c);
static inline char usart_rx_char(void);

/* ====== External Function Definitions ====== */

ISR(USART_RX_vect) { usart_on_rx_ready(); }

ISR(USART_TX_vect) { USART_ATOMIC_TX usart_on_tx_ready(); }

void usart_init(bool tx_buffered, bool tx_int) {
  if (tx_buffered) {
    usart_transmit = &usart_transmit_buffered;
    g_usart_tx_q = queue_char_create(USART_TX_Q_SIZE);
  } else {
    usart_transmit = &usart_transmit_unbuffered;
  }
  g_usart_rx_q = queue_char_create(USART_RX_Q_SIZE);
  UBRR0 = F_CPU / (USART_BAUD * 16UL) - 1;
  UCSR0C = USART_UCSZ_8_BIT << UCSZ00;
  UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (tx_int << TXCIE0) | (1 << RXCIE0);
}

char usart_receive(void) {
  while (queue_is_empty(g_usart_rx_q)) continue;
  return queue_char_pop(g_usart_rx_q);
}

void usart_flush(void) {
  while (!queue_is_empty(g_usart_tx_q)) {
    while (!usart_is_tx_ready()) continue;
    usart_on_tx_ready();
  }
}

/* ====== Static Function Definitions ====== */

static inline void usart_transmit_buffered(char c) {
  USART_ATOMIC_TX {
    if (queue_is_full(g_usart_tx_q)) return;
    queue_char_push(g_usart_tx_q, c);
    if (usart_is_tx_ready()) usart_on_tx_ready();
  }
}

static inline void usart_transmit_unbuffered(char c) {
  while (!usart_is_tx_ready()) continue;
  usart_tx_char(c);
}

static inline void usart_on_tx_ready(void) {
  if (queue_is_empty(g_usart_tx_q)) return;
  usart_tx_char(queue_char_pop(g_usart_tx_q));
}

static inline void usart_on_rx_ready(void) {
  do {
    queue_char_push(g_usart_rx_q, UDR0);
  } while (usart_is_rx_ready());
}

static inline bool usart_is_tx_ready(void) { return UCSR0A & (1 << UDRE0); }

static inline bool usart_is_rx_ready(void) { return UCSR0A & (1 << RXC0); }

static inline void usart_tx_char(char c) { UDR0 = c; }

static inline char usart_rx_char(void) { return UDR0; }

#endif
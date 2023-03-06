#include "usart.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#include "utils/queue.h"

#define USART_RX_Q_SIZE (127)
#define USART_TX_Q_SIZE (255)
#define USART_UCSZ_8_BIT (3)

static queue_t *g_usart_rx_q = NULL;
static queue_t *g_usart_tx_q = NULL;

ISR(USART_RX_vect) {
  do {
    queue_push(g_usart_rx_q, (void *)(intptr_t)UDR0);
  } while (UCSR0A & (1 << RXC0));
}

ISR(USART_TX_vect) {
  if (queue_is_empty(g_usart_tx_q)) return;
  UDR0 = (char)(intptr_t)queue_pop(g_usart_tx_q);
}

void usart_init() {
  g_usart_rx_q = queue_create(USART_RX_Q_SIZE);
  g_usart_tx_q = queue_create(USART_TX_Q_SIZE);
  UBRR0 = F_CPU / (USART_BAUD * 16UL) - 1;
  UCSR0C = USART_UCSZ_8_BIT << UCSZ00;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
}

void usart_transmit(char c) {
  if (UCSR0A & (1 << UDRE0)) {
    UDR0 = c;
  } else {
    queue_push(g_usart_tx_q, (void *)(intptr_t)c);
  }
}

char usart_receive(void) {
  while (queue_is_empty(g_usart_rx_q)) continue;
  char c = (char)(intptr_t)queue_pop(g_usart_rx_q);

  return c;
}

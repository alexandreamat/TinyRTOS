#include "usart.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#include "queue.h"

#define USART_RX_Q_SIZE (127)
#define USART_BAUD (9600)
#define USART_UBRR_VALUE (F_CPU / (USART_BAUD * 16UL) - 1)

static queue_t *g_usart_rx_q = NULL;

ISR(USART_RX_vect) {
  do {
    queue_add(g_usart_rx_q, UDR0);
  } while (UCSR0A & (1 << RXC0));
}

void usart_init() {
  g_usart_rx_q = queue_init(USART_RX_Q_SIZE);
  UBRR0H = (USART_UBRR_VALUE >> 8) & 0xFF;
  UBRR0L = (USART_UBRR_VALUE >> 0) & 0xFF;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

int usart_transmit(char c, FILE *stream) {
  if (c == '\n') usart_transmit('\r', stream);
  while (!(UCSR0A & (1 << UDRE0))) continue;
  UDR0 = c;
  return 0;
}

int usart_receive(FILE *stream) {
  while (queue_is_empty(g_usart_rx_q)) continue;
  return queue_remove(g_usart_rx_q);
}

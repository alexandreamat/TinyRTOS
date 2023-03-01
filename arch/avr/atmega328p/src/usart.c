#include "usart.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#include "utils/queue.h"

#define USART_RX_Q_SIZE (127)
#define USART_UCSZ_8_BIT (3)

static queue_t *g_usart_rx_q = NULL;

ISR(USART_RX_vect) {
  do {
    queue_push(g_usart_rx_q, (void *)(intptr_t)UDR0);
  } while (UCSR0A & (1 << RXC0));
}

void usart_init() {
  g_usart_rx_q = queue_create(USART_RX_Q_SIZE);
  UBRR0 = F_CPU / (USART_BAUD * 16UL) - 1;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  UCSR0C = USART_UCSZ_8_BIT << UCSZ00;
}

int usart_transmit(char c) {
  while (!(UCSR0A & (1 << UDRE0))) continue;
  UDR0 = c;
  return 0;
}

int usart_receive(void) {
  while (queue_is_empty(g_usart_rx_q)) continue;
  return (int)queue_pop(g_usart_rx_q);
}

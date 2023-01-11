#include "usart.h"

#include <avr/io.h>

#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (BAUD * 16UL)) - 1)

void USART_Init() {
  UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
  UBRR0L = (unsigned char)UBRR_VALUE;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

int USART_Transmit(char c, FILE *stream) {
  if (c == '\n') USART_Transmit('\r', stream);
  while (!(UCSR0A & (1 << UDRE0))) continue;
  UDR0 = c;
  return 0;
}

int USART_Receive(FILE *stream) {
  while (!(UCSR0A & (1 << RXC0))) continue;
  return UDR0;
}

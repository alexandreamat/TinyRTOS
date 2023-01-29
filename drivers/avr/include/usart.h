#include <stdio.h>

void usart_init();
int usart_transmit(char data, FILE *stream);
int usart_receive(FILE *stream);
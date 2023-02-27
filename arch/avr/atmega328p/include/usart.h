#ifndef __USART_H__
#define __USART_H__

#include <stdio.h>

void usart_init();
int usart_transmit(char data, FILE *stream);
int usart_receive(FILE *stream);

#endif  // __USART_H__

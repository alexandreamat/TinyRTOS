#ifndef __USART_H__
#define __USART_H__

#include <stdbool.h>
#include <stdio.h>

#define USART_BAUD (9600)

extern void (*usart_transmit)(char c);

void usart_init(bool tx_buffered, bool tx_int);
char usart_receive(void);
void usart_flush(void);

#endif  // __USART_H__

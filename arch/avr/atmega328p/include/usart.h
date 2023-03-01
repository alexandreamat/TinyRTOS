#ifndef __USART_H__
#define __USART_H__

#include <stdio.h>

#define USART_BAUD (9600)

void usart_init(void);
int usart_transmit(char data);
int usart_receive(void);

#endif  // __USART_H__

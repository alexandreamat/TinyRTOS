#include <stdio.h>

void USART_Init();
int USART_Transmit(char data, FILE *stream);
int USART_Receive(FILE *stream);
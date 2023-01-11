#include "serial_io.h"

#include <avr/io.h>
#include <stdio.h>

#include "usart.h"

void serial_io_init(void) {
  USART_Init();

  static FILE usart_stdout =
      FDEV_SETUP_STREAM(USART_Transmit, NULL, _FDEV_SETUP_WRITE);
  static FILE usart_stdin =
      FDEV_SETUP_STREAM(NULL, USART_Receive, _FDEV_SETUP_READ);
  stdout = &usart_stdout;
  stdin = &usart_stdin;
}
#include "serial_io.h"

#include <avr/io.h>
#include <stdio.h>

#include "usart.h"

void serial_io_init(void) {
  usart_init();

  static FILE usart_stdout =
      FDEV_SETUP_STREAM(usart_transmit, NULL, _FDEV_SETUP_WRITE);
  static FILE usart_stdin =
      FDEV_SETUP_STREAM(NULL, usart_receive, _FDEV_SETUP_READ);
  stdout = &usart_stdout;
  stdin = &usart_stdin;
}
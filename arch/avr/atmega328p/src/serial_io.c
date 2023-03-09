#include "hal/serial_io.h"

#include <stdio.h>

#include "usart.h"

static int serial_io_stdout_put(char c, FILE* stream);
static int serial_io_stdin_get(FILE* stream);

void serial_io_init(void) {
  usart_init(true, true);
  static FILE usart_stdout =
      FDEV_SETUP_STREAM(&serial_io_stdout_put, NULL, _FDEV_SETUP_WRITE);
  static FILE usart_stdin =
      FDEV_SETUP_STREAM(NULL, &serial_io_stdin_get, _FDEV_SETUP_READ);
  stdout = &usart_stdout;
  stdin = &usart_stdin;
}

static int serial_io_stdout_put(char c, FILE* stream) {
  (void)stream;
  if (c == '\n') serial_io_stdout_put('\r', NULL);
  usart_transmit(c);
  return 0;
}

static int serial_io_stdin_get(FILE* stream) {
  (void)stream;
  return (int)usart_receive();
}
#include <math.h>
#include <unistd.h>

#include "peripherals/auxiliaries/mini_uart.h"
#include "utils/morse.h"

void _exit(int status) {
  // Exit the program with the specified status code
  while (1)
    ;
}

int _close(int fd) {
  // Close the file descriptor
  (void)fd;
  return -1;
}

off_t _lseek(int fd, off_t offset, int whence) {
  // Reposition the file offset of the file descriptor
  (void)fd;
  (void)offset;
  (void)whence;
  return (off_t)-1;
}

ssize_t _read(int fd, void *buf, size_t count) {
  // Read from the file descriptor
  (void)fd;
  (void)buf;
  (void)count;
  return (ssize_t)-1;
}

void *_sbrk(ptrdiff_t incr) {
  // Increase the program's data space by incr bytes
  (void)incr;
  return (void *)-1;
}

ssize_t _write(int fd, const void *buf, size_t count) {
  for (size_t i = 0; i < count; i++) {
    mini_uart_putc(*(char *)buf++);
  }
  return count;
}

double __trunctfdf2(long double a) { return NAN; }
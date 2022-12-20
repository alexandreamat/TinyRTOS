#include "misc.h"

#include "gpio.h"

void delay(unsigned int ms) {
  register unsigned long frq, pct, r;

  asm volatile("mrs %0, cntfrq_el0" : "=r"(frq));
  asm volatile("mrs %0, cntpct_el0" : "=r"(pct));
  pct += (frq / 1000) * ms;
  do {
    asm volatile("mrs %0, cntpct_el0" : "=r"(r));
  } while (r < pct);
}

void sos(void) {
  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);

  gpio_set(42);
  delay(150);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(150);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(150);
  gpio_clear(42);
  delay(50);

  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);
  gpio_set(42);
  delay(50);
  gpio_clear(42);
  delay(50);
}
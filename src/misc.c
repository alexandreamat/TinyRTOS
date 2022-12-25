#include "misc.h"

#include "peripherals/gpio.h"

void delay(unsigned int ms) {
  register unsigned long frq, pct, r;

  asm volatile("mrs %0, cntfrq_el0" : "=r"(frq));
  asm volatile("mrs %0, cntpct_el0" : "=r"(pct));
  pct += (frq / 1000) * ms;
  do {
    asm volatile("mrs %0, cntpct_el0" : "=r"(r));
  } while (r < pct);
}

void mmio_write(long int reg, unsigned int val) {
  *(volatile unsigned int *)reg = val;
}

unsigned int mmio_read(long int reg) { return *(volatile unsigned int *)reg; }
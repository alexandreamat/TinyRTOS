#include "hal/interrupts.h"

#include <avr/interrupt.h>
#include <stdio.h>

#include "utils/morse.h"

void interrupts_init(void) { sei(); }

ISR(BADISR_vect) {
  morse_send_text("SOS");
  printf("Unexpected error\n");
}
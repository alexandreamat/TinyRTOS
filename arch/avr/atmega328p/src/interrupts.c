#include "hal/interrupts.h"

#include <avr/interrupt.h>
#include <stdio.h>

void interrupts_init(void) { sei(); }

ISR(BADISR_vect) { printf("Unexpected error\n"); }
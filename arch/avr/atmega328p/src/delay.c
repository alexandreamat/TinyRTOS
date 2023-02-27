#include "hal/delay.h"

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

void delay(unsigned int ms) { _delay_ms(ms); }

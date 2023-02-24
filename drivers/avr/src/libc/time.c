#include "libc/time.h"

#include <stdio.h>

#include "hw_timer.h"

clock_t clock(void) { return hw_timer_clock(); }

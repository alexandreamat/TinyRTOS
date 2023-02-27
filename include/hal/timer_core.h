#ifndef __TIMER_CORE_H__
#define __TIMER_CORE_H__

#include "libc/time.h"

typedef void (*timer_core_func_t)(void);

void timer_core_start(timer_core_func_t func, clock_t duration);

#endif  // __TIMER_CORE_H__

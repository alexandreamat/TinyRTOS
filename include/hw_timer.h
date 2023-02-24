#ifndef __HW_TIMER_H__
#define __HW_TIMER_H__

#include "libc/time.h"

#define HW_TIMER_CLOCK_PRESCALE (64)

typedef struct {
  void (*ref)(void*);
  void* arg;
} hw_timer_func_t;

void hw_timer_create(hw_timer_func_t* func, unsigned time_ms);

clock_t hw_timer_clock(void);

void hw_timer_start_clock(void);

#endif  // __HW_TIMER_H__

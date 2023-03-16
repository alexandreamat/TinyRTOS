#ifndef __TIMER_H__
#define __TIMER_H__

#include "libc/time.h"

typedef void (*timer_func_t)(void*);

typedef struct timer timer_t;

void timer_init(void);

void timer_deinit(void);

timer_t* timer_create(timer_func_t func, void* arg, unsigned time_ms);

#endif  // __TIMER_H__

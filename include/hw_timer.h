#ifndef __HW_TIMER_H__
#define __HW_TIMER_H__

typedef struct {
  void (*ref)(void*);
  void* arg;
} hw_timer_func_t;

void hw_timer_create(hw_timer_func_t* func, unsigned time_ms);

#endif  // __HW_TIMER_H__

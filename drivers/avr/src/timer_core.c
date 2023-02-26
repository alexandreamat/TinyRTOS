
#include "timer_core.h"

#include <stdlib.h>

#include "timer_counter.h"

static size_t timer_core_remaining_overflows = 0;
static uint8_t timer_core_remaining_clocks = 0;
static timer_core_func_t timer_core_func = NULL;

static void timer_core_on_overflow(void);
static void timer_core_on_match(void);

void timer_core_start(timer_core_func_t func, clock_t duration) {
  timer_core_func = func;
  timer_core_remaining_overflows = duration / TIMER_COUNTER_2_TCNT_MAX;
  timer_core_remaining_clocks = duration % TIMER_COUNTER_2_TCNT_MAX;
  timer_counter_2_set_attrs(TIMER_COUNTER_2_WGM_NORMAL, CLOCK_PRESCALE,
                            &timer_core_on_overflow, NULL, NULL);
  timer_core_on_overflow();
}

static void timer_core_on_overflow(void) {
  if (timer_core_remaining_overflows--) return;
  timer_counter_2_set_attrs(
      TIMER_COUNTER_2_WGM_NORMAL, CLOCK_PRESCALE, NULL,
      &(timer_counter_8_bit_output_t){.cb = &timer_core_on_match,
                                      .mode = TIMER_COUNTER_OUTPUT_MODE_NORMAL,
                                      .val = timer_core_remaining_clocks},
      NULL);
}

static void timer_core_on_match(void) {
  timer_counter_2_set_attrs(0, 0, NULL, NULL, NULL);
  timer_core_func();
  timer_core_remaining_overflows = 0;
  timer_core_remaining_clocks = 0;
  timer_core_func = NULL;
}
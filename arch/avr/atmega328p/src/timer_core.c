#include "hal/timer_core.h"

#include <stdio.h>
#include <stdlib.h>

#include "timer_counter.h"

/* ====== Static Variables ====== */

static size_t timer_core_remaining_overflows = 0;
static uint8_t timer_core_remaining_clocks = 0;
static timer_core_func_t timer_core_func = NULL;

/* ====== Static Function Declarations ====== */

static void timer_core_on_overflow(void);
static void timer_core_on_output_match(void);
static inline void timer_core_disarm_timer(void);
static inline void timer_core_arm_overflow_timer(void);
static inline void timer_core_arm_output_match_timer(void);

/* ====== External Function Definitions ====== */

void timer_core_start(timer_core_func_t func, clock_t duration) {
  timer_core_disarm_timer();
  timer_core_func = func;
  timer_core_remaining_overflows = duration / (TIMER_COUNTER_2_TCNT_MAX + 1);
  timer_core_remaining_clocks = duration % (TIMER_COUNTER_2_TCNT_MAX + 1);
  if (timer_core_remaining_overflows) {
    timer_core_arm_overflow_timer();
  } else {
    timer_core_arm_output_match_timer();
  }
}

void timer_core_stop(void) {
  timer_core_disarm_timer();
  timer_core_remaining_overflows = 0;
  timer_core_remaining_clocks = 0;
  timer_core_func = NULL;
}

/* ====== Static Function Definitions ====== */

static void timer_core_on_overflow(void) {
  if (--timer_core_remaining_overflows) return;
  timer_core_arm_output_match_timer();
}

static void timer_core_on_output_match(void) {
  timer_core_disarm_timer();
  timer_core_remaining_overflows = 0;
  timer_core_remaining_clocks = 0;
  timer_core_func_t func = timer_core_func;
  timer_core_func = NULL;
  func();
}

static inline void timer_core_arm_overflow_timer(void) {
  timer_counter_2_set_attrs(TIMER_COUNTER_2_WGM_NORMAL, CLOCK_PRESCALE,
                            &timer_core_on_overflow, NULL, NULL);
}

static inline void timer_core_arm_output_match_timer(void) {
  if (timer_core_remaining_clocks) {
    timer_counter_2_set_attrs(TIMER_COUNTER_2_WGM_NORMAL, CLOCK_PRESCALE, NULL,
                              &(timer_counter_8_bit_output_t){
                                  .cb = &timer_core_on_output_match,
                                  .mode = TIMER_COUNTER_OUTPUT_MODE_NORMAL,
                                  .val = timer_core_remaining_clocks},
                              NULL);
  } else {
    timer_core_on_output_match();
  }
}

static inline void timer_core_disarm_timer(void) {
  timer_counter_2_set_attrs(0, 0, NULL, NULL, NULL);
}
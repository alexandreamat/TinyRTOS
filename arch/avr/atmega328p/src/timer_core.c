#include "hal/timer_core.h"

#include <stdio.h>
#include <stdlib.h>

#include "timer_counter.h"
#include "utils/debug.h"

/* ====== Static Variables ====== */

static struct {
  unsigned prescaler;
  size_t remaining_overflows;
  uint16_t remaining_count;
  timer_core_func_t func;
  void (*arm_overflow_timer)(void);
  void (*arm_output_match_timer)(void);
  void (*disarm_timer)(void);
} timer_core = {0};

/* ====== Static Function Declarations ====== */

static void timer_core_set_attrs(clock_t duration);
static void timer_core_on_overflow(void);
static void timer_core_on_output_match(void);
static void timer_core_disarm_timer_1(void);
static void timer_core_disarm_timer_2(void);
static void timer_core_arm_overflow_timer_1(void);
static void timer_core_arm_overflow_timer_2(void);
static void timer_core_arm_output_match_timer_1(void);
static void timer_core_arm_output_match_timer_2(void);

/* ====== External Function Definitions ====== */

void timer_core_start(timer_core_func_t func, clock_t duration) {
  // set func and duration
  timer_core.func = func;
  // set remaining overflows, prescaler, and arm and disarm callbacks
  timer_core_set_attrs(duration);
  // arm timer/counter
  if (!timer_core.prescaler) {
    timer_core_on_output_match();
    return;
  }
  if (timer_core.remaining_overflows) {
    timer_core.arm_overflow_timer();
  } else {
    timer_core.arm_output_match_timer();
  }
}

void timer_core_stop(void) {
  if (!timer_core.disarm_timer) return;
  timer_core.disarm_timer();
  timer_core.remaining_overflows = 0;
  timer_core.remaining_count = 0;
  timer_core.func = NULL;
}

/* ====== Static Function Definitions ====== */

static void timer_core_set_attrs(clock_t duration) {
  for (size_t i = TIMER_COUNTER_1_PRESCALERS_SIZE - 1; i > 0; i--) {
    uint32_t duration_count =
        duration * CYCLES_PER_CLOCK / TIMER_COUNTER_1_PRESCALERS[i];
    // breakpoint();
    if (TIMER_COUNTER_1_SIZE >= duration_count) continue;
    timer_core.prescaler = TIMER_COUNTER_1_PRESCALERS[i];
    timer_core.remaining_overflows = duration_count / TIMER_COUNTER_1_SIZE;
    timer_core.remaining_count = duration_count % TIMER_COUNTER_1_SIZE;
    timer_core.arm_overflow_timer = &timer_core_arm_overflow_timer_1;
    timer_core.arm_output_match_timer = &timer_core_arm_output_match_timer_1;
    timer_core.disarm_timer = &timer_core_disarm_timer_1;
    return;
  }
  for (size_t i = TIMER_COUNTER_2_PRESCALERS_SIZE - 2; i > 0; i--) {
    uint16_t duration_count =
        duration * CYCLES_PER_CLOCK / TIMER_COUNTER_2_PRESCALERS[i];
    if (TIMER_COUNTER_2_SIZE >= duration_count) continue;
    timer_core.prescaler = TIMER_COUNTER_2_PRESCALERS[i];
    timer_core.remaining_overflows = duration_count / TIMER_COUNTER_2_SIZE;
    timer_core.remaining_count = duration_count % TIMER_COUNTER_2_SIZE;
    timer_core.arm_overflow_timer = &timer_core_arm_overflow_timer_2;
    timer_core.arm_output_match_timer = &timer_core_arm_output_match_timer_2;
    timer_core.disarm_timer = &timer_core_disarm_timer_2;
    return;
  }
  return;
}

static void timer_core_on_overflow(void) {
  if (--timer_core.remaining_overflows) return;
  if (timer_core.remaining_count) {
    timer_core.arm_output_match_timer();
  } else {
    timer_core_on_output_match();
  }
}

static void timer_core_on_output_match(void) {
  timer_core.disarm_timer();
  timer_core.remaining_overflows = 0;
  timer_core.remaining_count = 0;
  timer_core.prescaler = 0;
  timer_core.disarm_timer = NULL;
  timer_core.arm_overflow_timer = NULL;
  timer_core.arm_output_match_timer = NULL;
  timer_core_func_t func = timer_core.func;
  timer_core.func = NULL;
  func();
}

static void timer_core_arm_overflow_timer_1(void) {
  timer_counter_1_set_attrs(TIMER_COUNTER_1_WGM_NORMAL, timer_core.prescaler,
                            &timer_core_on_overflow, NULL, NULL, NULL);
}

static void timer_core_arm_overflow_timer_2(void) {
  timer_counter_2_set_attrs(TIMER_COUNTER_2_WGM_NORMAL, timer_core.prescaler,
                            &timer_core_on_overflow, NULL, NULL);
}

static void timer_core_arm_output_match_timer_1(void) {
  timer_counter_1_set_attrs(
      TIMER_COUNTER_1_WGM_NORMAL, timer_core.prescaler, NULL,
      &(timer_counter_16_bit_output_t){.cb = &timer_core_on_output_match,
                                       .mode = TIMER_COUNTER_OUTPUT_MODE_NORMAL,
                                       .val = timer_core.remaining_count},
      NULL, NULL);
}

static void timer_core_arm_output_match_timer_2(void) {
  timer_counter_2_set_attrs(TIMER_COUNTER_2_WGM_NORMAL, timer_core.prescaler,
                            NULL,
                            &(timer_counter_8_bit_output_t){
                                .cb = &timer_core_on_output_match,
                                .mode = TIMER_COUNTER_OUTPUT_MODE_NORMAL,
                                .val = (uint8_t)timer_core.remaining_count},
                            NULL);
}

static void timer_core_disarm_timer_1(void) {
  timer_counter_1_set_attrs(0, 0, NULL, NULL, NULL, NULL);
}

static void timer_core_disarm_timer_2(void) {
  timer_counter_2_set_attrs(0, 0, NULL, NULL, NULL);
}
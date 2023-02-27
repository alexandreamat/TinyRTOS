#include "libc/time.h"

#include <stdio.h>

#include "timer_counter.h"

/* ====== Preprocessor Definitions ====== */

/* ====== Static Variables ====== */

static size_t clock_overflow_count = 0;

clock_t __CLOCKS_PER_SEC__ = F_CPU / CLOCK_PRESCALE;

/* ====== Static Function Declarations ====== */

static void clock_on_overflow(void);

/* ====== External Function Definitions ====== */

void clock_start(void) {
  timer_counter_0_set_attrs(TIMER_COUNTER_0_WGM_NORMAL, CLOCK_PRESCALE,
                            &clock_on_overflow, NULL, NULL);
}

clock_t clock(void) {
  return clock_overflow_count * (clock_t)TIMER_COUNTER_0_TCNT_MAX +
         timer_counter_0_get_count();
}

/* ====== Static Function Definitions ====== */

static void clock_on_overflow(void) { clock_overflow_count++; }

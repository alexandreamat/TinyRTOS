#include "libc/time.h"

#include "timer_counter.h"

#define CLOCK_PRESCALE (64)

const clock_t CLOCKS_PER_SEC = F_CPU / CLOCK_PRESCALE;
const unsigned long CYCLES_PER_CLOCK =
    CLOCK_PRESCALE * (TIMER_COUNTER_0_TCNT_MAX + 1);

static size_t clock_overflow_count = 0;

static void clock_on_overflow(void) { clock_overflow_count++; }

void clock_start(void) {
  timer_counter_0_set_attrs(TIMER_COUNTER_0_WGM_NORMAL, CLOCK_PRESCALE,
                            &clock_on_overflow, NULL, NULL);
}

clock_t clock(void) { return clock_overflow_count; }

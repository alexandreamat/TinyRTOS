#include "kernel/timer.h"

#include <stdbool.h>
#include <stdio.h>

#include "hal/timer_core.h"
#include "libc/time.h"
#include "utils/debug.h"
#include "utils/min_heap.h"

/* ====== Preprocessor Definitions ====== */

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)

/* ====== Type Definitions ====== */

struct timer {
  timer_func_t func;
  void* arg;
  clock_t deadline;
};

/* ====== Static Variables ====== */

static min_heap_t* timer_heap = NULL;

/* ====== Static Function Declarations ====== */

static int timer_cmp(timer_t* a, timer_t* b);
static void timer_print(timer_t* timer);
static void timer_run_expired_and_schedule_next(void);

/* ====== External Function Definitions ====== */

void timer_init(void) {
  timer_heap = min_heap_create((min_heap_cmp_t)&timer_cmp,
                               (min_heap_print_t)&timer_print);
}

void timer_deinit(void) {
  min_heap_free(timer_heap);
  timer_heap = NULL;
}

timer_t* timer_create(timer_func_t func, void* arg, unsigned int time_ms) {
  timer_core_stop();
  timer_t* timer = calloc(1, sizeof(timer_t));
  timer->func = func;
  timer->arg = arg;
  timer->deadline = clock() + (clock_t)(time_ms * CLOCKS_PER_MS);
  min_heap_push(timer_heap, (void*)timer);
  timer_run_expired_and_schedule_next();
  return timer;
}

/* ====== Static Function Definitions ====== */

static int timer_cmp(timer_t* a, timer_t* b) {
  return a->deadline > b->deadline ? 1 : -1;
}

static void timer_print(timer_t* timer) { printf("%u", (intptr_t)timer->arg); }

static void timer_run_expired_and_schedule_next(void) {
  timer_t* timer;
  timer = (timer_t*)min_heap_peek(timer_heap);
  if (!timer) return;
  clock_t now = clock();
  while (timer->deadline <= now) {
    min_heap_pop(timer_heap);
    timer->func(timer->arg);
    free(timer);
    timer = (timer_t*)min_heap_peek(timer_heap);
    if (!timer) return;
    now = clock();
  }
  timer_core_start(&timer_run_expired_and_schedule_next, timer->deadline - now);
}

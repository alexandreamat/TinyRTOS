#ifndef __TIME_H__
#define __TIME_H__

#include <time.h>

#ifdef CLOCKS_PER_SEC
#undef CLOCKS_PER_SEC
#endif

extern const clock_t CLOCKS_PER_SEC;
extern const unsigned long CYCLES_PER_CLOCK;

void clock_start(void);

clock_t clock(void);

#endif  // __TIME_H__

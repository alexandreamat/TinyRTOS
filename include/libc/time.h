#ifndef __TIME_H__
#define __TIME_H__

#include <time.h>

#ifdef CLOCKS_PER_SEC
#undef CLOCKS_PER_SEC
#endif

#define CLOCKS_PER_SEC (__CLOCKS_PER_SEC__)

extern clock_t __CLOCKS_PER_SEC__;

clock_t clock(void);

#endif  // __TIME_H__
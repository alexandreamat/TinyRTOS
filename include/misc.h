#ifndef __MISC_H__
#define __MISC_H__

#define SYS_CLOCK_FREQ (500000000)

#define BOOL2STR(x) (x ? "true" : "false")

void delay(unsigned int ms);

extern int get_CurrentEL(void);

void mmio_write(long int reg, unsigned int val);

unsigned int mmio_read(long int reg);

#endif  // __MISC_H__
#ifndef __MMIO_H__
#define __MMIO_H__

void mmio_write(long int reg, unsigned int val);

unsigned int mmio_read(long int reg);

#endif  // __MMIO_H__
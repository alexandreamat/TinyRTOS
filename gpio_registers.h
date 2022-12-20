#ifndef __GPIO_REGISTERS_H__
#define __GPIO_REGISTERS_H__

#include "base_registers.h"

#define GPFSEL0 (GP_BASE + 0x00)
#define GPFSEL1 (GP_BASE + 0x04)
#define GPFSEL2 (GP_BASE + 0x08)
#define GPFSEL3 (GP_BASE + 0x0C)
#define GPFSEL4 (GP_BASE + 0x10)
#define GPFSEL5 (GP_BASE + 0x14)
#define GPSET0 (GP_BASE + 0x1C)
#define GPSET1 (GP_BASE + 0x20)
#define GPCLR0 (GP_BASE + 0x28)
#define GPCLR1 (GP_BASE + 0x2C)
#define GPLEV0 (GP_BASE + 0x34)
#define GPLEV1 (GP_BASE + 0x38)
#define GPEDS0 (GP_BASE + 0x40)
#define GPEDS1 (GP_BASE + 0x44)
#define GPREN0 (GP_BASE + 0x4C)
#define GPREN1 (GP_BASE + 0x50)
#define GPFEN0 (GP_BASE + 0x58)
#define GPFEN1 (GP_BASE + 0x5C)
#define GPHEN0 (GP_BASE + 0x64)
#define GPHEN1 (GP_BASE + 0x68)
#define GPLEN0 (GP_BASE + 0x70)
#define GPLEN1 (GP_BASE + 0x74)
#define GPAREN0 (GP_BASE + 0x7C)
#define GPAREN1 (GP_BASE + 0x80)
#define GPAFEN0 (GP_BASE + 0x88)
#define GPAFEN1 (GP_BASE + 0x8C)
#define GPIO_PUP_PDN_CNTRL_REG0 (GP_BASE + 0xE4)
#define GPIO_PUP_PDN_CNTRL_REG1 (GP_BASE + 0xE8)
#define GPIO_PUP_PDN_CNTRL_REG2 (GP_BASE + 0xEC)
#define GPIO_PUP_PDN_CNTRL_REG3 (GP_BASE + 0xF0)

#endif  // __GPIO_REGISTERS_H__
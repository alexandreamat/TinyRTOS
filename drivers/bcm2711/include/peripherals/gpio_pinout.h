#ifndef __GPIO_PINTOUT_H__
#define __GPIO_PINTOUT_H__

#include "peripherals/base.h"

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

#define SDA1 (2)
#define SCL1 (3)
#define GPIO_GCLK (4)

#define GPIO_GEN0 (17)
#define GPIO_GEN2 (27)
#define GPIO_GEN3 (22)

#define SPI_MOSI (10)
#define SPI_MISO (9)
#define SPI_SCLK (11)

#define TXD0 (14)
#define RXD0 (15)
#define GPIO_GEN1 (18)

#define GPIO_GEN4 (23)
#define GPIO_GEN5 (24)

#define GPIO_GEN6 (25)
#define SPI_CE0_N (8)
#define SPI_CE1_N (7)

typedef enum {
  GPFSEL_FUNC_INPUT = 0b000,   // GPIO Pin is an input
  GPFSEL_FUNC_OUTPUT = 0b001,  // GPIO Pin is an output
  GPFSEL_FUNC_ALT0 = 0b100,    // GPIO Pin takes alternate function 0
  GPFSEL_FUNC_ALT1 = 0b101,    // GPIO Pin takes alternate function 1
  GPFSEL_FUNC_ALT2 = 0b110,    // GPIO Pin takes alternate function 2
  GPFSEL_FUNC_ALT3 = 0b111,    // GPIO Pin takes alternate function 3
  GPFSEL_FUNC_ALT4 = 0b011,    // GPIO Pin takes alternate function 4
  GPFSEL_FUNC_ALT5 = 0b010     // GPIO Pin takes alternate function 5
} gpfsel_func_t;

typedef enum {
  GPIO_PULL_STATE_NONE = 0b00,  // No resistor is selected
  GPIO_PULL_STATE_UP = 0b01,    // Pull up resistor is selected
  GPIO_PULL_STATE_DOWN = 0b10,  // Pull down resistor is selected
} gpio_pup_pdn_t;

#endif  // __GPIO_PINTOUT_H__
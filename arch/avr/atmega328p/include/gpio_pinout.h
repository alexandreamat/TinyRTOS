#ifndef __GPIO_PINOUT_H__
#define __GPIO_PINOUT_H__

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#define GPIO_PB (000)
#define GPIO_PC (010)
#define GPIO_PD (020)

#define GPIO_PB0 (GPIO_PB | PB0)
#define GPIO_PB1 (GPIO_PB | PB1)
#define GPIO_PB2 (GPIO_PB | PB2)
#define GPIO_PB3 (GPIO_PB | PB3)
#define GPIO_PB4 (GPIO_PB | PB4)
#define GPIO_PB5 (GPIO_PB | PB5)
#define GPIO_PB6 (GPIO_PB | PB6)
#define GPIO_PB7 (GPIO_PB | PB7)

#define GPIO_PC0 (GPIO_PC | PC0)
#define GPIO_PC1 (GPIO_PC | PC1)
#define GPIO_PC2 (GPIO_PC | PC2)
#define GPIO_PC3 (GPIO_PC | PC3)
#define GPIO_PC4 (GPIO_PC | PC4)
#define GPIO_PC5 (GPIO_PC | PC5)
#define GPIO_PC6 (GPIO_PC | PC6)
#define GPIO_PC7 (GPIO_PC | PC7)

#define GPIO_PD0 (GPIO_PD | PD0)
#define GPIO_PD1 (GPIO_PD | PD1)
#define GPIO_PD2 (GPIO_PD | PD2)
#define GPIO_PD3 (GPIO_PD | PD3)
#define GPIO_PD4 (GPIO_PD | PD4)
#define GPIO_PD5 (GPIO_PD | PD5)
#define GPIO_PD6 (GPIO_PD | PD6)
#define GPIO_PD7 (GPIO_PD | PD7)

#endif  // __GPIO_PINOUT_H__

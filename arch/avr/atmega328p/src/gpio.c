#include "hal/gpio.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gpio_pinout.h"
#include "misc.h"

#define GPIO_REG(deref, pin, step) \
  ((reg8_t *)(_SFR_MEM_ADDR(deref) + (pin) / CHAR_BIT * (step)))

#define GPIO_PORT(pin) GPIO_REG(PORTB, pin, 3u)
#define GPIO_DDR(pin) GPIO_REG(DDRB, pin, 3u)
#define GPIO_PIN(pin) GPIO_REG(PINB, pin, 3u)
#define GPIO_PCMSK(pin) GPIO_REG(PCMSK0, pin, 1u)

#define GPIO_BIT(x) (x % CHAR_BIT)
#define GPIO_COUNT (3 * CHAR_BIT)

const int GPIO_ACT_LED = GPIO_PB5;

typedef struct {
  bool level;
  gpio_event_callback_t cb;
} gpio_state_t;

static gpio_state_t *g_gpio_states[GPIO_COUNT] = {0};

static void pcint_isr_vector(uint8_t i);

static void gpio_set(pin_t pin);
static void gpio_clear(pin_t pin);

ISR(PCINT0_vect) { pcint_isr_vector(PCIF0); }

ISR(PCINT1_vect) { pcint_isr_vector(PCIF1); }

ISR(PCINT2_vect) { pcint_isr_vector(PCIF2); }

void gpio_pull(pin_t pin, gpio_pull_t value) {
  reg8_t *reg = GPIO_PORT(pin);
  *reg &= ~(1 << GPIO_BIT(pin));
  *reg |= (uint8_t)value << GPIO_BIT(pin);
}

void gpio_select_function(pin_t pin, gpio_func_t func) {
  reg8_t *reg = GPIO_DDR(pin);
  *reg &= ~(1 << GPIO_BIT(pin));
  *reg |= (uint8_t)func << GPIO_BIT(pin);
}

void gpio_toggle(pin_t pin) {
  reg8_t *reg = GPIO_PORT(pin);
  *reg ^= 1 << GPIO_BIT(pin);
}

bool gpio_read(pin_t pin) {
  reg8_t *reg = GPIO_PIN(pin);
  return (*reg >> GPIO_BIT(pin)) & 1;
}

void gpio_write(pin_t pin, bool level) {
  if (level) {
    gpio_set(pin);
  } else {
    gpio_clear(pin);
  }
}

void gpio_install_event_callback(pin_t pin, gpio_event_callback_t cb) {
  PCICR |= 1 << (pin / CHAR_BIT);
  reg8_t *reg = GPIO_PCMSK(pin);
  *reg |= 1 << GPIO_BIT(pin);
  g_gpio_states[pin] = malloc(sizeof(gpio_state_t));
  g_gpio_states[pin]->cb = cb;
  g_gpio_states[pin]->level = gpio_read(pin);
}

static void pcint_isr_vector(uint8_t i) {
  for (uint8_t j = 0; j < CHAR_BIT; j++) {
    pin_t pin = i * CHAR_BIT + j;
    gpio_state_t *state = g_gpio_states[pin];
    if (!state) continue;
    bool level = gpio_read(pin);
    if (level == state->level) continue;
    state->level = level;
    state->cb(level);
  }
}

static void gpio_set(pin_t pin) {
  reg8_t *reg = GPIO_PORT(pin);
  *reg |= 1 << GPIO_BIT(pin);
}

static void gpio_clear(pin_t pin) {
  reg8_t *reg = GPIO_PORT(pin);
  *reg &= ~(1 << GPIO_BIT(pin));
}
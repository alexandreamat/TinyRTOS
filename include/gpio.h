#include <stdbool.h>
#include <stdint.h>

extern const int GPIO_ACT_LED;

typedef uint8_t pin_t;

typedef enum {
  GPIO_FUNC_INPUT = 0,
  GPIO_FUNC_OUTPUT = 1,
} gpio_func_t;

typedef enum {
  GPIO_PULL_NONE = 0,
  GPIO_PULL_UP = 1,
} gpio_pull_t;

typedef void (*gpio_event_callback_t)(bool);

void gpio_select_function(pin_t pin, gpio_func_t func);
void gpio_pull(pin_t pin, gpio_pull_t value);

void gpio_toggle(pin_t pin);
bool gpio_read(pin_t pin);
void gpio_write(pin_t pin, bool level);
void gpio_install_event_callback(pin_t pin, gpio_event_callback_t cb);

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

int gpio_set(unsigned int pin_number);

int gpio_clear(unsigned int pin_number);

int gpio_pull(unsigned int pin_number, unsigned int value);

int gpio_select_function(unsigned int pin_number, gpfsel_func_t func);
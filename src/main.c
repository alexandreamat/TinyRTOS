#include <stdio.h>

#include "hal/delay.h"
#include "hal/gpio.h"
#include "hal/interrupts.h"
#include "hal/serial_io.h"
#include "libc/time.h"
#include "utils/morse.h"

#define SLEEP_MS 1000

int main(void) {
  gpio_select_function(GPIO_ACT_LED, GPIO_FUNC_OUTPUT);
  morse_send_text("START");
  interrupts_init();
  serial_io_init();
  printf("Starting TinyRTOS...\n");
  clock_start();
  while (1) {
    system_tick();
    gpio_toggle(GPIO_ACT_LED);
    delay(1000);
  }
  printf("End of the program.\n");
}

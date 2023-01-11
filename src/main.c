
#include <stdio.h>

// #include "delay.h"
#include <util/delay.h>

#include "gpio.h"
#include "interrupts.h"
#include "morse.h"
#include "projects/02_spaceship_interface.h"
#include "serial_io.h"

#define SLEEP_MS 1000

int main(void) {
  gpio_select_function(GPIO_ACT_LED, GPIO_FUNC_OUTPUT);
  morse_send_text("SOS");
  serial_io_init();

  printf("Starting TinyRTOS\n");

  interrupts_init();

  project_02_spaceship_interface_start();

  while (1) {
    gpio_toggle(GPIO_ACT_LED);
    _delay_ms(SLEEP_MS);
    // delay(SLEEP_MS);
    printf("alive\n");
  }

  printf("End of the program\n");
}

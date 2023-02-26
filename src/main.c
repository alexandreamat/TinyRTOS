
#include <stdio.h>

#include "delay.h"
#include "gpio.h"
#include "interrupts.h"
#include "libc/time.h"
#include "morse.h"
#include "projects/02_spaceship_interface.h"
#include "projects/11_crystal_ball.h"
#include "serial_io.h"

#define SLEEP_MS 1000

int main(void) {
  gpio_select_function(GPIO_ACT_LED, GPIO_FUNC_OUTPUT);
  morse_send_text("SOS");
  serial_io_init();

  printf("Starting TinyRTOS\n");

  interrupts_init();
  clock_start();

  while (1) {
    gpio_toggle(GPIO_ACT_LED);
    delay(SLEEP_MS);
  }

  printf("End of the program\n");
}

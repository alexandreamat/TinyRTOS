
#include <stdio.h>

#include "hal/delay.h"
#include "hal/gpio.h"
#include "hal/interrupts.h"
#include "hal/serial_io.h"
#include "hal/timer_core.h"
#include "kernel/sched.h"
#include "libc/time.h"
#include "posix/pthread.h"
#include "posix/unistd.h"
#include "utils/min_heap.h"
#include "utils/morse.h"

#define SLEEP_MS 1000

void* led_toggle(void* _) {
  (void)_;
  while (1) {
    gpio_toggle(GPIO_ACT_LED);
    sleep(3);
  }
}

void* keep_alive(void* _) {
  (void)_;
  while (1) {
    morse_send_text("O");
    sleep(4);
  }
}

void send_point(void) { putchar('.'); }

int main(void) {
  gpio_select_function(GPIO_ACT_LED, GPIO_FUNC_OUTPUT);
  morse_send_text("SOS");
  serial_io_init();
  printf("Starting TinyRTOS\n");

  interrupts_init();
  clock_start();

  while (1) {
    system_tick();
    printf("current time %lu\n", clock() / CLOCKS_PER_SEC);
    printf("current time %lu\n", time(NULL));
    gpio_toggle(GPIO_ACT_LED);
    delay(1000);
  }

  printf("End of the program\n");
}

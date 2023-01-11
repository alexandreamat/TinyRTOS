#include <stdio.h>

#include "delay.h"
#include "gpio.h"

#if defined(AVR)
#include "gpio_pinout.h"
#define BUTTON_GPIO (GPIO_PD2)
#define LED_1_GPIO (GPIO_PD3)
#define LED_2_GPIO (GPIO_PD4)
#define LED_3_GPIO (GPIO_PD5)
#elif defined(BCM2711)
#define BUTTON_GPIO (GPIO_PD2)
#define LED_1_GPIO (GPIO_PD3)
#define LED_2_GPIO (GPIO_PD4)
#define LED_3_GPIO (GPIO_PD5)
#endif

static bool g_blink = false;

void button_event(bool level) { g_blink = level; }

void project_02_spaceship_interface_start(void) {
  gpio_select_function(BUTTON_GPIO, GPIO_FUNC_INPUT);
  gpio_select_function(LED_1_GPIO, GPIO_FUNC_OUTPUT);
  gpio_select_function(LED_2_GPIO, GPIO_FUNC_OUTPUT);
  gpio_select_function(LED_3_GPIO, GPIO_FUNC_OUTPUT);

  gpio_pull(BUTTON_GPIO, GPIO_PULL_NONE);

  gpio_install_event_callback(BUTTON_GPIO, &button_event);

  while (1) {
    if (g_blink) {
      gpio_clear(LED_1_GPIO);
      gpio_toggle(LED_2_GPIO);
      gpio_toggle(LED_3_GPIO);
    } else {
      gpio_set(LED_1_GPIO);
      gpio_clear(LED_2_GPIO);
      gpio_clear(LED_3_GPIO);
    }
    delay(100);
  }
}

#include "peripherals/hd44780u.h"

#include <assert.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "gpio_pinout.h"
#include "hal/gpio.h"

typedef enum { CLEAR_DISPLAY_FLAG = 1 << 0 } hd_44780u_clear_display_t;

typedef enum { RETURN_HOME_FLAG = 1 << 1 } hd_44780u_return_home_t;

typedef enum {
  ENTRY_MODE_SET_SHIFT = 1 << 0,
  ENTRY_MODE_SET_INCREMENT = 1 << 1,
  ENTRY_MODE_SET_FLAG = 1 << 2,
} hd_44780u_entry_mode_set_bit_t;

typedef enum {
  DISPLAY_ON_OFF_CONTROL_BLINK = 1 << 0,
  DISPLAY_ON_OFF_CONTROL_CURSOR = 1 << 1,
  DISPLAY_ON_OFF_CONTROL_DISPLAY = 1 << 2,
  DISPLAY_ON_OFF_CONTROL_FLAG = 1 << 3,
} hd_44780u_display_on_off_control_bit_t;

typedef enum {
  CURSOR_OR_DISPLAY_SHIFT_RIGHT = 1 << 2,
  CURSOR_OR_DISPLAY_SHIFT_DISPLAY = 1 << 3,
  CURSOR_OR_DISPLAY_SHIFT_FLAG = 1 << 4,
} hd_44780u_cursor_or_display_shift_r;

typedef enum {
  FUNCTION_SET_IS5X10 = 1 << 2,
  FUNCTION_SET_IS2LINE = 1 << 3,
  FUNCTION_SET_IS8BIT = 1 << 4,
  FUNCTION_SET_FLAG = 1 << 5,
} hd_44780u_function_set_r;

typedef enum { SET_CGRAM_ADDR_FLAG = 1 << 6 } hd_44780u_set_cgram_addr_t;

typedef enum { SET_DDRAM_ADDR_FLAG = 1 << 7 } hd_44780u_set_addram_addr_t;

typedef enum {
  ADDR = 1 << 0,
  IS_BUSY = 1 << 7,
} hd44780u_read_busy_flag_and_address_counter_t;

static const pin_t RS_PIN = GPIO_PB2;
static const pin_t RW_PIN = GPIO_PB3;
static const pin_t EN_PIN = GPIO_PB4;
static volatile uint8_t* const PORT_ADDR = (uint8_t*)_SFR_MEM_ADDR(PORTD);
static volatile uint8_t* const DDR_ADDR = (uint8_t*)_SFR_MEM_ADDR(DDRD);
static const uint8_t PORT_MASK = 0xF0;
static const uint16_t SMALL_DELAY = 1 << 8;
static const uint8_t BIG_DELAY = 100;

static void hd44780u_write_instruction(bool rs, uint8_t data, bool is4bit);
static void hd44780u_write_to_port(uint8_t data);
static inline void hd4478u_return_home();

void hd44780u_init() {
  gpio_select_function(RS_PIN, GPIO_FUNC_OUTPUT);
  gpio_select_function(RW_PIN, GPIO_FUNC_OUTPUT);
  gpio_select_function(EN_PIN, GPIO_FUNC_OUTPUT);

  uint8_t data = 0;

  data = FUNCTION_SET_FLAG | FUNCTION_SET_IS8BIT;
  hd44780u_write_instruction(false, data, false);
  hd44780u_write_instruction(false, data, false);
  data &= ~FUNCTION_SET_IS8BIT;
  hd44780u_write_instruction(false, data, false);
  data |= FUNCTION_SET_IS2LINE;
  hd44780u_write_instruction(false, data, true);

  hd44780u_write_instruction(false, CLEAR_DISPLAY_FLAG, true);
  hd4478u_return_home();

  data = ENTRY_MODE_SET_FLAG | ENTRY_MODE_SET_INCREMENT;
  hd44780u_write_instruction(false, data, true);

  data = DISPLAY_ON_OFF_CONTROL_FLAG | DISPLAY_ON_OFF_CONTROL_DISPLAY |
         DISPLAY_ON_OFF_CONTROL_BLINK | DISPLAY_ON_OFF_CONTROL_CURSOR;
  hd44780u_write_instruction(false, data, true);
}

void hd44780u_load_character_patterns(size_t size, const uint8_t cps[size][8]) {
  hd44780u_write_instruction(false, SET_CGRAM_ADDR_FLAG, true);
  for (uint8_t i = 0; i < size; i++)
    for (uint8_t j = 0; j < 8; j++)
      hd44780u_write_instruction(true, cps[i][j], true);
  hd44780u_write_instruction(false, SET_DDRAM_ADDR_FLAG | 0, true);
  for (uint8_t i = 0; i < size; i++) hd44780u_write_instruction(true, i, true);
}

void hd44780u_move_left() {
  hd44780u_write_instruction(false, CURSOR_OR_DISPLAY_SHIFT_FLAG, true);
}

void hd44780u_move_right() {
  uint8_t data = CURSOR_OR_DISPLAY_SHIFT_FLAG | CURSOR_OR_DISPLAY_SHIFT_RIGHT;
  hd44780u_write_instruction(false, data, true);
}

void hd44780u_move_up() {
  for (uint8_t i = 0; i < 40; i++) hd44780u_move_left();
}

void hd44780u_move_down() {
  for (uint8_t i = 0; i < 40; i++) hd44780u_move_right();
}

void hd44780u_write_string(char* s) {
  while (*s) hd44780u_write_char(*s++);
}

void hd44780u_write_char(char c) {
  hd44780u_write_instruction(true, (uint8_t)c, true);
}

static inline void hd4478u_return_home() {
  hd44780u_write_instruction(false, RETURN_HOME_FLAG, true);
}

static void hd44780u_write_instruction(bool rs, uint8_t data, bool is4bit) {
  _delay_us(BIG_DELAY);
  *DDR_ADDR |= PORT_MASK;
  gpio_write(RS_PIN, rs);
  gpio_write(RW_PIN, false);
  _delay_us(SMALL_DELAY);
  hd44780u_write_to_port((data << 0) & PORT_MASK);
  if (is4bit) hd44780u_write_to_port((data << 4) & PORT_MASK);
  gpio_write(RS_PIN, false);
}

static void hd44780u_write_to_port(uint8_t data) {
  gpio_write(EN_PIN, true);
  *PORT_ADDR |= data & PORT_MASK;
  _delay_us(SMALL_DELAY);
  gpio_write(EN_PIN, false);
  _delay_us(SMALL_DELAY);
  *PORT_ADDR &= ~PORT_MASK;
}

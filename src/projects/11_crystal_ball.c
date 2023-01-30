#include "projects/11_crystal_ball.h"

#include <assert.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "hd44780u.h"

static const char ESC = '\033';
static const char DEL = '\177';
static const uint8_t CPS[8][8] = {
    {
        0b00010,  // ni 1
        0b00100,  //
        0b01001,  //
        0b10100,  //
        0b00101,  //
        0b00101,  //
        0b00100,  //
        0b00100,  //
    },
    {
        0b01000,  // ni 2
        0b11111,  //
        0b00010,  //
        0b01000,  //
        0b01010,  //
        0b01010,  //
        0b01000,  //
        0b11000,  //
    },
    {
        0b00100,  // hao 2
        0b00100,  //
        0b01000,  //
        0b11111,  //
        0b01001,  //
        0b01110,  //
        0b00011,  //
        0b00100,  //
    },
    {
        0b01110,  // hao 2
        0b00010,  //
        0b00100,  //
        0b11111,  //
        0b00100,  //
        0b00100,  //
        0b00100,  //
        0b01100,  //
    },
    // {
    //     0b00110,  // wo 1
    //     0b01100,  //
    //     0b00100,  //
    //     0b11111,  //
    //     0b00100,  //
    //     0b10100,  //
    //     0b01100,  //
    //     0b00000,  //
    // },
    // {
    //     0b00100,  // wo 2
    //     0b10010,  //
    //     0b10000,  //
    //     0b11111,  //
    //     0b01000,  //
    //     0b01110,  //
    //     0b01001,  //
    //     0b10110,  //
    // },
    // {
    //     0b11111,  // ai 1
    //     0b01001,  //
    //     0b11111,  //
    //     0b10001,  //
    //     0b00111,  //
    //     0b00101,  //
    //     0b01000,  //
    //     0b10001,  //
    // },
    // {
    //     0b11110,  // ai 2
    //     0b00100,  //
    //     0b11111,  //
    //     0b00001,  //
    //     0b11100,  //
    //     0b11000,  //
    //     0b10000,  //
    //     0b01000,  //
    // },
    {
        0b11111,  // hong 1
        0b00001,  //
        0b11111,  //
        0b10000,  //
        0b11111,  //
        0b00001,  //
        0b01001,  //
        0b00110,  //
    },
    {
        0b00000,  // hong 2
        0b01000,  //
        0b01000,  //
        0b10000,  //
        0b10010,  //
        0b10011,  //
        0b11101,  //
        0b00000,  //
    },
    {
        0b00100,  // zhou 1
        0b00100,  //
        0b00100,  //
        0b10110,  //
        0b01101,  //
        0b00100,  //
        0b01000,  //
        0b10000,  //
    },
    {
        0b00010,  // zhou 2
        0b10010,  //
        0b10010,  //
        0b11010,  //
        0b10110,  //
        0b10010,  //
        0b00010,  //
        0b00010,  //
    },
};

void project_11_crystal_ball_start(void) {
  hd44780u_init();
  hd44780u_write_string("Hello world!");
  (void)CPS;
  // hd44780u_load_character_patterns(4, CPS);
  while (1) {
    char c = '\0';
    c = getc(stdin);
    if (ESC == c) {
      c = getc(stdin);
      if ('[' != c) {
        printf("Unrecognised keystroke: \\033%c\n", c);
        continue;
      }
      c = getc(stdin);
      switch (c) {
        case 'A':
          hd44780u_move_up();
          break;
        case 'B':
          hd44780u_move_down();
          break;
        case 'C':
          hd44780u_move_right();
          break;
        case 'D':
          hd44780u_move_left();
          break;
        default:
          printf("Unrecognised keystroke: \\033[%c\n", c);
          break;
      }
    } else if (DEL == c) {
      hd44780u_move_left();
      hd44780u_write_char(' ');
      hd44780u_move_left();
    } else if ('\r' == c) {
    } else {
      putc(c, stdout);
      hd44780u_write_char(c);
    }
  }
}

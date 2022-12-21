#include "morse.h"

#include "gpio.h"
#include "misc.h"

#define MORSE_PIN (42)
#define MORSE_UNIT_MS (50)
#define MORSE_LINE_MS (MORSE_UNIT_MS * 3)
#define MORSE_DOT_MS (MORSE_UNIT_MS * 1)
#define MORSE_PARTS_SEP_MS (MORSE_UNIT_MS * 1)
#define MORSE_LETTER_SEP_MS (MORSE_UNIT_MS * 3)
#define MORSE_WORDS_SEP_MS (MORSE_UNIT_MS * 7)

static const char* ascii_to_morse[] = {
    ['A'] = ".-",    ['B'] = "-...",  ['C'] = "-.-.",  ['D'] = "-..",
    ['E'] = ".",     ['F'] = "..-.",  ['G'] = "--.",   ['H'] = "....",
    ['I'] = "..",    ['J'] = ".---",  ['K'] = "-.-",   ['L'] = ".-..",
    ['M'] = "--",    ['N'] = "-.",    ['O'] = "---",   ['P'] = ".--.",
    ['Q'] = "--.-",  ['R'] = ".-.",   ['S'] = "...",   ['T'] = "-",
    ['U'] = "..-",   ['V'] = "...-",  ['W'] = ".--",   ['X'] = "-..-",
    ['Y'] = "-.--",  ['Z'] = "--..",  ['1'] = ".----", ['2'] = "..---",
    ['3'] = "...--", ['4'] = "....-", ['5'] = ".....", ['6'] = "-....",
    ['7'] = "--...", ['8'] = "---..", ['9'] = "----.", ['0'] = "-----"};

static char* morse_send_word(char* word);
static void morse_send_letter(char letter);
static void morse_send_dot();
static void morse_send_line();

void morse_send_text(char* text) {
  while (*text) {
    if (' ' != *text) {
      text = morse_send_word(text);
    } else {
      text++;
    }
  }
}

static char* morse_send_word(char* word) {
  while ('\0' != *word && ' ' != *word) {
    morse_send_letter(*word++);
  }
  delay(MORSE_WORDS_SEP_MS - MORSE_LETTER_SEP_MS);
  return word;
}

static void morse_send_letter(char letter) {
  const char* morse = ascii_to_morse[(int)letter];
  while (*morse) {
    switch (*morse++) {
      case '-':
        morse_send_line();
        break;
      case '.':
        morse_send_dot();
        break;
    }
  }
  delay(MORSE_LETTER_SEP_MS - MORSE_PARTS_SEP_MS);
}

static void morse_send_dot() {
  gpio_set(MORSE_PIN);
  delay(MORSE_DOT_MS);
  gpio_clear(MORSE_PIN);
  delay(MORSE_PARTS_SEP_MS);
}

static void morse_send_line() {
  gpio_set(MORSE_PIN);
  delay(MORSE_LINE_MS);
  gpio_clear(MORSE_PIN);
  delay(MORSE_PARTS_SEP_MS);
}

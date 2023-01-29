#include <stdint.h>
#include <stdlib.h>

void hd44780u_init(void);
void hd44780u_load_character_patterns(size_t size, const uint8_t cps[size][8]);
void hd44780u_move_left(void);
void hd44780u_move_up(void);
void hd44780u_move_down(void);
void hd44780u_move_right(void);
void hd44780u_write_string(char* s);
void hd44780u_write_char(char c);
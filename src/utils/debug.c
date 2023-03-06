#include "utils/debug.h"

#include <ctype.h>
#include <stdio.h>

void hexdump(const void* data, size_t size) {
  const unsigned char* p = (const unsigned char*)data;
  unsigned char c;
  size_t i, j;
  for (i = 0; i < size; i += 16) {
    printf("%06zx:", i);
    for (j = 0; j < 16; ++j) {
      if (i + j < size) {
        printf(" %02x", p[i + j]);
      } else {
        printf("   ");
      }
    }
    printf("  ");
    for (j = 0; j < 16; ++j) {
      if (i + j < size) {
        c = p[i + j];
        if (isprint(c)) {
          putchar(c);
        } else {
          putchar('.');
        }
      } else {
        putchar(' ');
      }
    }
    printf("\n");
  }
}

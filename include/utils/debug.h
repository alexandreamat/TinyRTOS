#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <libc/time.h>
#include <stddef.h>
#include <stdio.h>

#define LOG(fmt, ...) \
  printf("(%lu) [%s:%u] " fmt "\n", clock(), __func__, __LINE__, ##__VA_ARGS__)

#define DEBUG_VAR(fmt, a) LOG("" #a " = " fmt "", a)

void hexdump(const void* data, size_t size);

#endif  // __DEBUG_H__

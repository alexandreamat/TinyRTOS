#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  char* arr;
  size_t buf_size;
  size_t tail;
  size_t head;
} queue_t;

void queue_init(queue_t* q, char* buf, size_t buf_size);

void queue_add(queue_t* q, char val);

char queue_remove(queue_t* q);

char queue_peek(queue_t* q);

bool queue_is_empty(queue_t* q);

#endif  // __QUEUE_H__
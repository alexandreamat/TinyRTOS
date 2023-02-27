#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  void** arr;
  size_t size;
  size_t tail;
  size_t head;
} queue_t;

queue_t* queue_create(size_t size);

void queue_free(queue_t* q);

void queue_push(queue_t* q, void* val);

void* queue_pop(queue_t* q);

void* queue_peek(queue_t* q);

bool queue_is_empty(queue_t* q);

#endif  // __QUEUE_H__

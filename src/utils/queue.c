#include "utils/queue.h"

#include <stdbool.h>
#include <stdlib.h>

queue_t* queue_create(size_t size) {
  queue_t* q = calloc(1, sizeof(queue_t));
  q->size = size + 1;
  q->arr = calloc(q->size, sizeof(char));
  return q;
}

void queue_free(queue_t* q) {
  free(q->arr);
  free(q);
}

void queue_push(queue_t* q, void* val) {
  q->arr[q->tail++] = val;
  q->tail %= q->size;
}

void* queue_pop(queue_t* q) {
  void* val = q->arr[q->head++];
  q->tail %= q->size;
  return val;
}

void* queue_peek(queue_t* q) { return q->arr[q->head]; }

bool queue_is_empty(queue_t* q) { return q->head == q->tail; }

#include "queue.h"

#include <stdbool.h>
#include <stdlib.h>

queue_t* queue_init(size_t size) {
  queue_t* q = calloc(1, sizeof(queue_t));
  q->size = size + 1;
  q->arr = calloc(q->size, sizeof(char));
  return q;
}

void queue_add(queue_t* q, char val) { q->arr[q->tail++] = val; }

char queue_remove(queue_t* q) { return q->arr[q->head++]; }

char queue_peek(queue_t* q) { return q->arr[q->head]; }

bool queue_is_empty(queue_t* q) { return q->head == q->tail; }

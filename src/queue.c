#include "queue.h"

#include <stdbool.h>

void queue_init(queue_t* q, char* buf, size_t buf_size) {
  q->buf_size = buf_size;
  q->arr = buf;
}

void queue_add(queue_t* q, char val) { q->arr[q->tail++] = val; }

char queue_remove(queue_t* q) { return q->arr[q->head++]; }

char queue_peek(queue_t* q) { return q->arr[q->head]; }

bool queue_is_empty(queue_t* q) { return q->head == q->tail; }

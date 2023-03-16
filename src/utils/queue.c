

#include "utils/queue.h"

#include <stdlib.h>
#include <string.h>

/* ====== Type definitions ====== */

struct queue {
  char* arr;
  size_t size;
  size_t item_size;
  size_t tail;
  size_t head;
};

/* ====== External Function Definitions ====== */

queue_t* queue_create(size_t queue_size, size_t item_size) {
  queue_t* q = calloc(1, sizeof(queue_t));
  q->size = queue_size + 1;
  q->item_size = item_size;
  q->arr = calloc(q->size, item_size);
  return q;
}

void queue_free(queue_t* q) {
  free(q->arr);
  free(q);
}

void queue_push(queue_t* q, void* val) {
  memcpy(&q->arr[q->tail], val, q->item_size);
  q->tail += q->item_size;
  q->tail %= q->size * q->item_size;
}

void queue_pop(queue_t* q, void* val) {
  memcpy(val, &q->arr[q->head], q->item_size);
  q->head += q->item_size;
  q->head %= q->size * q->item_size;
}

bool queue_is_empty(queue_t* q) { return q->head == q->tail; }

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>
#include <stddef.h>

#define QUEUE_DEFINE_TYPE_FUNCTIONS(T)                               \
                                                                     \
  static inline queue_t* queue_##T##_create(size_t size) {           \
    return queue_create(size, sizeof(T));                            \
  }                                                                  \
                                                                     \
  static inline void queue_##T##_free(queue_t* q) { queue_free(q); } \
                                                                     \
  static inline void queue_##T##_push(queue_t* q, T val) {           \
    queue_push(q, (void*)&val);                                      \
  }                                                                  \
                                                                     \
  static inline T queue_##T##_pop(queue_t* q) {                      \
    T val;                                                           \
    queue_pop(q, (void*)&val);                                       \
    return val;                                                      \
  }                                                                  \
                                                                     \
  static inline bool queue_##T##_is_empty(queue_t* q) {              \
    return queue_is_empty(q);                                        \
  }

typedef struct queue queue_t;

queue_t* queue_create(size_t size, size_t item_size);

void queue_free(queue_t* q);

void queue_push(queue_t* q, void* val);

void queue_pop(queue_t* q, void* val);

bool queue_is_empty(queue_t* q);

QUEUE_DEFINE_TYPE_FUNCTIONS(char)

QUEUE_DEFINE_TYPE_FUNCTIONS(int)

#endif  // __QUEUE_H__

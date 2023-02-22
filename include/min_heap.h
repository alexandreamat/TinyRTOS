#ifndef __MIN_HEAP_H__
#define __MIN_HEAP_H__

#include <stdlib.h>

typedef struct min_heap_node_s min_heap_node_t;

struct min_heap_node_s {
  void* val;
  min_heap_node_t* parent;
  min_heap_node_t* left;
  min_heap_node_t* right;
};

typedef struct {
  min_heap_node_t* root;
  size_t size;
} min_heap_t;

min_heap_t* min_heap_create(void);

void min_heap_free(min_heap_t* heap);

void min_heap_push(min_heap_t* heap, void* val);

void* min_heap_pop(min_heap_t* heap);

void min_heap_print(min_heap_t* heap);

#endif  // __MIN_HEAP_H__

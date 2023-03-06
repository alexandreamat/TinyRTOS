#ifndef __MIN_HEAP_H__
#define __MIN_HEAP_H__

#include <stdlib.h>

typedef struct min_heap min_heap_t;

typedef int (*min_heap_cmp_t)(void*, void*);

min_heap_t* min_heap_create(min_heap_cmp_t cmp);

void min_heap_free(min_heap_t* heap);

void min_heap_push(min_heap_t* heap, void* val);

void* min_heap_pop(min_heap_t* heap);

void* min_heap_peek(min_heap_t* heap);

void min_heap_print(min_heap_t* heap);

#endif  // __MIN_HEAP_H__

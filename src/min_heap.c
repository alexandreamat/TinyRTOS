#include "min_heap.h"

#include <stdio.h>
#include <stdlib.h>

/* ====== Preprocessor Definitions ====== */

/* ====== Type Definitions ====== */

/* ====== Static Variables ====== */

/* ====== Static Function Declarations ====== */

static void min_heap_node_free(min_heap_node_t* node);

static min_heap_node_t* min_heap_push_bottom(min_heap_t* heap, void* val);

static void* min_heap_pop_bottom(min_heap_t* heap);

static void min_heap_node_heap_up(min_heap_node_t* node);

static void min_heap_node_heap_down(min_heap_node_t* node);

static inline void min_heap_swap(void** a, void** b);

static void min_heap_node_print(min_heap_node_t* node, size_t indent);

/* ====== External Function Definitions ====== */

min_heap_t* min_heap_create(void) { return calloc(1, sizeof(min_heap_t)); }

void min_heap_free(min_heap_t* heap) {
  min_heap_node_free(heap->root);
  free(heap);
}

void min_heap_push(min_heap_t* heap, void* val) {
  min_heap_node_t* last = min_heap_push_bottom(heap, val);
  min_heap_node_heap_up(last);
}

void* min_heap_pop(min_heap_t* heap) {
  void* val = heap->root->val;
  heap->root->val = min_heap_pop_bottom(heap);
  min_heap_node_heap_down(heap->root);
  return val;
}

void min_heap_print(min_heap_t* heap) {
  printf("Heap size = %u\n", heap->size);
  if (heap->root) {
    min_heap_node_print(heap->root, 0);
  } else {
    puts("Heap is empty\n");
  }
}

/* ====== Static Function Definitions ====== */

static void min_heap_node_free(min_heap_node_t* node) {
  if (!node) return;
  min_heap_node_free(node->left);
  min_heap_node_free(node->right);
}

static min_heap_node_t* min_heap_push_bottom(min_heap_t* heap, void* val) {
  if (0 == heap->size) {
    heap->root = calloc(1, sizeof(min_heap_node_t));
    heap->root->val = val;
    heap->size = 1;
    return heap->root;
  }

  size_t height = 0;
  while ((1u << height) - 1 <= heap->size) height++;
  size_t n = heap->size - (1 << (height - 1)) + 1;

  min_heap_node_t* parent = NULL;
  min_heap_node_t* node = heap->root;
  for (size_t mask = 1 << (height - 2); mask > 0; mask >>= 1) {
    parent = node;
    node = n & mask ? node->right : node->left;
  }

  node = calloc(1, sizeof(min_heap_node_t));
  node->val = val;
  node->parent = parent;
  if (n & 1u) {
    parent->right = node;
  } else {
    parent->left = node;
  }
  heap->size++;
  return node;
}

static void* min_heap_pop_bottom(min_heap_t* heap) {
  if (1 == heap->size) {
    void* val = heap->root->val;
    free(heap->root);
    heap->root = NULL;
    heap->size = 0;
    return val;
  }

  size_t height = 0;
  while ((1u << height) - 1 < heap->size) height++;
  size_t n = heap->size - (1 << (height - 1)) + 1;

  min_heap_node_t* parent = NULL;
  min_heap_node_t* node = heap->root;
  size_t mask = 1 << (height - 2);
  for (; mask > 0; mask >>= 1) {
    parent = node;
    node = (n - 1) & mask ? node->right : node->left;
  }

  void* val = node->val;
  free(node);
  if ((n - 1) & 1u) {
    parent->right = NULL;
  } else {
    parent->left = NULL;
  }
  heap->size--;
  return val;
}

static void min_heap_node_heap_up(min_heap_node_t* node) {
  if (!node) return;
  if (!node->parent) return;
  if (node->val < node->parent->val) {
    min_heap_swap(&node->val, &node->parent->val);
  }
  min_heap_node_heap_up(node->parent);
}

static void min_heap_node_heap_down(min_heap_node_t* node) {
  if (!node) return;
  if (node->right) {
    if (node->val < node->left->val && node->val < node->right->val) return;
    if (node->left->val < node->right->val) {
      min_heap_swap(&node->left->val, &node->val);
      min_heap_node_heap_down(node->left);
    } else {
      min_heap_swap(&node->right->val, &node->val);
      min_heap_node_heap_down(node->right);
    }
  } else if (node->left) {
    if (node->val < node->left->val) return;
    min_heap_swap(&node->left->val, &node->val);
    min_heap_node_heap_down(node->left);
  }
}

static inline void min_heap_swap(void** a, void** b) {
  void* tmp = *a;
  *a = *b;
  *b = tmp;
}

static void min_heap_node_print(min_heap_node_t* node, size_t indent) {
  if (!node) return;
  min_heap_node_print(node->right, indent + 4);
  for (int i = 0; i < indent; i++) putchar(' ');
  printf("%p\n", node->val);
  min_heap_node_print(node->left, indent + 4);
}
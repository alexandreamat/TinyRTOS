#include "utils/min_heap.h"

#include <stdio.h>
#include <stdlib.h>

/* ====== Type Definitions ====== */

typedef struct min_heap_node_s min_heap_node_t;

struct min_heap_node_s {
  void* val;
  min_heap_node_t* parent;
  min_heap_node_t* left;
  min_heap_node_t* right;
};

struct min_heap {
  min_heap_node_t* root;
  size_t size;
  min_heap_cmp_t cmp;
  min_heap_print_t print;
};

/* ====== Static Function Declarations ====== */

static void min_heap_node_free(min_heap_node_t* node);

static min_heap_node_t* min_heap_push_bottom(min_heap_t* heap, void* val);

static void* min_heap_pop_bottom(min_heap_t* heap);

static void min_heap_node_heap_up(min_heap_cmp_t cmp, min_heap_node_t* node);

static void min_heap_node_heap_down(min_heap_cmp_t cmp, min_heap_node_t* node);

static inline void min_heap_swap(void** a, void** b);

static void min_heap_node_print(min_heap_node_t* node, size_t indent,
                                min_heap_print_t print_val_cb);

/* ====== External Function Definitions ====== */

min_heap_t* min_heap_create(min_heap_cmp_t cmp, min_heap_print_t print) {
  min_heap_t* heap = calloc(1, sizeof(min_heap_t));
  heap->cmp = cmp;
  heap->print = print;
  return heap;
}

void min_heap_free(min_heap_t* heap) {
  min_heap_node_free(heap->root);
  free(heap);
}

void min_heap_push(min_heap_t* heap, void* val) {
  min_heap_node_t* last = min_heap_push_bottom(heap, val);
  min_heap_node_heap_up(heap->cmp, last);
}

void* min_heap_pop(min_heap_t* heap) {
  void* val = heap->root->val;
  heap->root->val = min_heap_pop_bottom(heap);
  min_heap_node_heap_down(heap->cmp, heap->root);
  return val;
}

void* min_heap_peek(min_heap_t* heap) {
  return heap->size ? heap->root->val : NULL;
}

void min_heap_print(min_heap_t* heap) {
  printf("Heap size = %u\n", heap->size);
  if (heap->root) {
    min_heap_node_print(heap->root, 0, heap->print);
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

static void min_heap_node_heap_up(min_heap_cmp_t cmp, min_heap_node_t* node) {
  if (!node) return;
  if (!node->parent) return;
  if (cmp(node->parent->val, node->val) > 0) {
    min_heap_swap(&node->val, &node->parent->val);
  }
  min_heap_node_heap_up(cmp, node->parent);
}

static void min_heap_node_heap_down(min_heap_cmp_t cmp, min_heap_node_t* node) {
  if (!node) return;
  if (node->right) {
    if (cmp(node->left->val, node->val) > 0 &&
        cmp(node->right->val, node->val) > 0)
      return;
    if (cmp(node->right->val, node->left->val) > 0) {
      min_heap_swap(&node->left->val, &node->val);
      min_heap_node_heap_down(cmp, node->left);
    } else {
      min_heap_swap(&node->right->val, &node->val);
      min_heap_node_heap_down(cmp, node->right);
    }
  } else if (node->left) {
    if (cmp(node->left->val, node->val) > 0) return;
    min_heap_swap(&node->left->val, &node->val);
    min_heap_node_heap_down(cmp, node->left);
  }
}

static inline void min_heap_swap(void** a, void** b) {
  void* tmp = *a;
  *a = *b;
  *b = tmp;
}

static void min_heap_node_print(min_heap_node_t* node, size_t indent,
                                min_heap_print_t print) {
  if (!node) return;
  min_heap_node_print(node->right, indent + 4, print);
  for (size_t i = 0; i < indent; i++) putchar(' ');
  print(node->val);
  putchar('\n');
  min_heap_node_print(node->left, indent + 4, print);
}
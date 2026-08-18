#include "pool.h"
#include "log.h"
#include <stdlib.h>

#define POOL_BLOCK_MIN_SIZE sizeof(void *)

typedef struct FreeBlock {
  struct FreeBlock *next;
} FreeBlock;

Result pool_create(Pool *pool, size_t block_size, size_t block_count) {
  if (!pool)
    return result_err(RESULT_ERR_NULL, "pool_create: NULL pointer");

  if (block_count == 0)
    return result_err(RESULT_ERR_ALLOC, "pool_create: block_count is 0");

  size_t actual =
      block_size < POOL_BLOCK_MIN_SIZE ? POOL_BLOCK_MIN_SIZE : block_size;

  pool->buffer = (unsigned char *)malloc(actual * block_count);
  if (!pool->buffer) {
    log_error("pool_create: allocation failed (%zu x %zu)", actual,
              block_count);
    return result_err(RESULT_ERR_ALLOC, "pool_create: malloc failed");
  }

  pool->block_size = actual;
  pool->block_count = block_count;
  pool->free_count = block_count;

  for (size_t i = 0; i < block_count - 1; i++) {
    FreeBlock *curr = (FreeBlock *)(pool->buffer + i * actual);
    curr->next = (FreeBlock *)(pool->buffer + (i + 1) * actual);
  }

  FreeBlock *last = (FreeBlock *)(pool->buffer + (block_count - 1) * actual);
  last->next = NULL;
  pool->free_list = (FreeBlock *)pool->buffer;

  log_info("Pool created: %zu blocks x %zu bytes", block_count, actual);
  return result_ok();
}

void *pool_alloc(Pool *pool) {
  if (!pool || !pool->free_list || pool->free_count == 0) {
    log_warn("pool_alloc: no free blocks available");
    return NULL;
  }

  FreeBlock *block = (FreeBlock *)pool->free_list;
  pool->free_list = block->next;
  pool->free_count--;
  return block;
}

void pool_free(Pool *pool, void *ptr) {
  if (!pool || !ptr)
    return;

  if (!pool_owns(pool, ptr)) {
    log_error("pool_free: pointer does not belong to this pool");
    return;
  }

  FreeBlock *block = (FreeBlock *)ptr;
  block->next = (FreeBlock *)pool->free_list;
  pool->free_list = block;
  pool->free_count++;
}

void pool_destroy(Pool *pool) {
  if (pool && pool->buffer) {
    free(pool->buffer);
    pool->buffer = NULL;
    pool->block_size = 0;
    pool->block_count = 0;
    pool->free_count = 0;
    pool->free_list = NULL;
    log_info("Pool destroyed");
  }
}

size_t pool_get_block_size(const Pool *pool) {
  return pool ? pool->block_size : 0;
}

size_t pool_get_free_count(const Pool *pool) {
  return pool ? pool->free_count : 0;
}

size_t pool_get_block_count(const Pool *pool) {
  return pool ? pool->block_count : 0;
}

int pool_owns(const Pool *pool, const void *ptr) {
  if (!pool || !ptr)
    return 0;

  const unsigned char *p = (const unsigned char *)ptr;
  return p >= pool->buffer &&
         p < pool->buffer + pool->block_size * pool->block_count;
}

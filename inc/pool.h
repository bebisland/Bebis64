#ifndef BEBIS64_POOL_H
#define BEBIS64_POOL_H

#include "result.h"
#include <stddef.h>

typedef struct Pool {
  unsigned char *buffer;
  size_t block_size;
  size_t block_count;
  size_t free_count;
  void *free_list;
} Pool;

Result pool_create(Pool *pool, size_t block_size, size_t block_count);
void *pool_alloc(Pool *pool);
void pool_free(Pool *pool, void *ptr);
void pool_destroy(Pool *pool);
size_t pool_get_block_size(const Pool *pool);
size_t pool_get_free_count(const Pool *pool);
size_t pool_get_block_count(const Pool *pool);
int pool_owns(const Pool *pool, const void *ptr);

#endif // BEBIS64_POOL_H

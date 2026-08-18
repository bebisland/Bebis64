#ifndef BEBIS64_ARENA_H
#define BEBIS64_ARENA_H

#include "result.h"
#include <stddef.h>

#define ARENA_ALIGNMENT 16

typedef struct Arena {
  unsigned char *buffer;
  size_t capacity;
  size_t offset;
} Arena;

Result  arena_create(Arena *arena, size_t capacity);
void   *arena_alloc(Arena *arena, size_t size);
void   *arena_alloc_aligned(Arena *arena, size_t size, size_t alignment);
void    arena_reset(Arena *arena);
void    arena_destroy(Arena *arena);
size_t  arena_get_offset(const Arena *arena);
size_t  arena_get_capacity(const Arena *arena);
size_t  arena_get_remaining(const Arena *arena);

#endif // BEBIS64_ARENA_H

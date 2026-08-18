#include "arena.h"
#include "log.h"
#include <stdlib.h>

static size_t align_up(size_t value, size_t alignment)
{
	return (value + alignment - 1) & ~(alignment - 1);
}

Result arena_create(Arena *arena, size_t capacity)
{
	if (!arena)
		return result_err(RESULT_ERR_NULL,
				  "arena_create: NULL pointer");

	arena->buffer = (unsigned char *)malloc(capacity);
	if (!arena->buffer) {
		log_error("arena_create: allocation failed (%zu bytes)",
			  capacity);
		return result_err(RESULT_ERR_ALLOC,
				  "arena_create: malloc failed");
	}

	arena->capacity = capacity;
	arena->offset = 0;

	log_info("Arena created: %zu bytes", capacity);
	return result_ok();
}

void *arena_alloc(Arena *arena, size_t size)
{
	return arena_alloc_aligned(arena, size, ARENA_ALIGNMENT);
}

void *arena_alloc_aligned(Arena *arena, size_t size, size_t alignment)
{
	if (!arena || !arena->buffer)
		return NULL;

	if (size == 0)
		return NULL;

	size_t aligned = align_up(arena->offset, alignment);
	if (aligned + size > arena->capacity) {
		log_error(
		    "arena_alloc: out of memory (requested %zu, remaining %zu)",
		    size, arena->capacity - arena->offset);
		return NULL;
	}

	void *ptr = arena->buffer + aligned;
	arena->offset = aligned + size;
	return ptr;
}

void arena_reset(Arena *arena)
{
	if (arena)
		arena->offset = 0;
}

void arena_destroy(Arena *arena)
{
	if (arena && arena->buffer) {
		free(arena->buffer);
		arena->buffer = NULL;
		arena->capacity = 0;
		arena->offset = 0;
		log_info("Arena destroyed");
	}
}

size_t arena_get_offset(const Arena *arena)
{
	return arena ? arena->offset : 0;
}

size_t arena_get_capacity(const Arena *arena)
{
	return arena ? arena->capacity : 0;
}

size_t arena_get_remaining(const Arena *arena)
{
	if (!arena)
		return 0;
	return arena->capacity - arena->offset;
}

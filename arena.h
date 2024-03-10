/* Basic Arena allocator for Windows.
 *
 * Copyright (c) 2024 xDahl
 * */

#pragma once
#include <windows.h>
#include <string.h>

#include "types.h" // u8, u64


typedef struct {
	u8 *start;
	u8 *end;
} Arena;


u8 *arena_init(Arena *a, u64 size)
{
	a->start = VirtualAlloc(0, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	a->end = a->start;
	return a->end;
}

u8 *arena_alloc(Arena *a, u64 size, int align)
{
	if (align > 1) a->end += (u64)align - ((u64)a->end & ((u64)align - 1));
	u8 *ret = memset(a->end, 0, size);
	a->end += size;
	return ret;
}

void arena_reset(Arena *a) { a->end = a->start; }
void arena_close(Arena *a) { VirtualFree((LPVOID)a->start, 0, MEM_RELEASE); }

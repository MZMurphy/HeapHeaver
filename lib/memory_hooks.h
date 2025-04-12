#ifndef MEMORY_HOOKS_H
#define MEMORY_HOOKS_H

#include<stddef.h> // for size_t

// Function pointers.

extern void*(*original_malloc)(size_t size);

extern void*(*original_calloc)(size_t nmemb, size_t size);

extern void*(*original_realloc)(void *ptr, size_t size);

extern void(*original_free)(void *ptr);

#endif // MEMORY_HOOKS_H

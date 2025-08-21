#ifndef MEMORY_BOOKKEEPING_H
#define MEMORY_BOOKKEEPING_H

#include <stddef.h>     // For size_t
#include "node.h"   // For MemoryNode struct

void add_node(void* address, size_t size);

int remove_node(void* address);

MemoryNode* search_nodes(void* address);

void print_nodes(void);

int modify_node(void* old_address, void* new_address, size_t new_size);

void clean_memory_bookkeeping(void);

#endif 
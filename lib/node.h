#ifndef NODE_H
#define NODE_H
#include <stddef.h>

/*
* Node struct for the memory allocation linked list aka 'memory_bookkeeping'
*/
typedef struct MemoryNode{
    void* address;  // Memory address.
    size_t size;    // Allocation size.
    struct MemoryNode* next; // Pointer to next node. 
} MemoryNode;

#endif // NODE_H
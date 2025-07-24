#define DEBUG_PRINT 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "memory_hooks.h"
#include "log.h"

// Global variables.
int malloc_count, calloc_count, realloc_count, free_count;
int malloc_allocation, calloc_allocation, realloc_allocation;
int realloc_deallocation, free_deallocation;
int total_allocation, total_dealloation;


// Hooks. 
void free(void* ptr)
{
    DEBUG("\nFree Hook Entered.");
    original_free(ptr);
    
    // counts... find deallocation count through tree. 
}

void* malloc(size_t size)
{
    write(1, "malloc hook entered.\n", 22);

    //puts("\nunder original_malloc");

    void* result = original_malloc(size);
    // add counts 
    // add to bookkeeping
    write(1, "malloc hook end.\n", 17);
    return result; 
} 

void* calloc(size_t nmemb, size_t size)
{
    write(1, "In calloc\n", 11);
    write(1, "Leaving calloc\n", 16);
    // counts and bookkeeping
}

void* realloc(void* ptr, size_t size)
{
    ;
    // lots of logic here
    // counts and add to bookkeeping
    // remove from bookkeepig
    // act as free
    // at as malloc
    // retunr null
    // move memory block - smaller, larger, same
    // unmove memory block - smaller, larger, same
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "memory_hooks.h"
#define DEBUG_PRINT 1
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
    write(1, "\nIN MALLOC WRITE\n", 18);
    original_free(ptr);
    
    // counts... find deallocation count through tree. 
}

void* malloc(size_t size)
{
    DEBUG("\nMalloc Hook Entered.");

    void* result = original_malloc(size);

    if(result == NULL){return result;}

    //Update counts and allocation size.
    malloc_count++;
    malloc_allocation +=size;
    total_allocation +=size;

    // To do:
    // add to bookkeeping system, likely linkedlist.
    DEBUG("\nMalloc Hook Exited.");
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


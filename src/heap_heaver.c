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

   if(original_free != NULL)
   {
    original_free(ptr);
   }else{
    write(2, "Error: original_free is NULL\n", 29);
    exit(1);
   }

   // Update counts and deallocations

   free_count++;

   // Free does not inherently know the size of the memory it is freeing...
   // Need to track this.

   DEBUG("\nFree Hook Exited·");
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
    DEBUG("\nCalloc Hook Entered.");

    void* result = original_calloc(nmemb, size);

    if(result == NULL){return result;}
    
    // Update counts and allocation sizes.
    calloc_count++;
    calloc_allocation += (nmemb * size);
    total_allocation += (nmemb * size);

    DEBUG("\nCalloc Hook Exited.");
    return result;
}

void* realloc(void* ptr, size_t size)
{
    DEBUG("\nRealloc Hook Entered.");

    void* result = original_realloc(ptr, size);

    if(result == NULL){return result;}

    // Update counts and allocation size...
    realloc_count++;
    realloc_allocation += size;
    total_allocation += size;

    // Realloc() like free() does not inherently know the size of the ptr it is being passed.
    // We need to utilise the same bookkeeping mechanism as free...
    // With the additional complexity of all the possible versions of realloc at play.
    // See man realloc

    // lots of logic here
    // counts and add to bookkeeping
    // remove from bookkeepig
    // act as free
    // at as malloc
    // retunr null
    // move memory block - smaller, larger, same
    // unmove memory block - smaller, larger, same
    DEBUG("\nRealloc Hook Exited.");
    return result;
}

int heap_report(void)
{
    char buffer[1024];
    int len;

    // White header.
    write(1, "\033[1;37m", 7);
    len = sprintf(buffer, "\n=====================================");
    write(1, buffer, len);
    len = sprintf(buffer, "\n     HeapHeaver Memory Report      ");
    write(1, buffer, len);
    len = sprintf(buffer, "\n=====================================");
    write(1, buffer, len);

    // Reset the colour.
    write(1, "\033[0m", 4);

    len = sprintf(buffer, "\nMemory Operation Counts:\n");
    write(1, buffer, len);

    len = sprintf(buffer, " Malloc: %d\n Calloc: %d\n Realloc: %d\n Free %d\n ", 
                    malloc_count, calloc_count, realloc_count, free_count);
    write(1, buffer, len);

    len = sprintf(buffer, "\nMemory Allocation (bytes):\n");
    write(1, buffer, len);

    len = sprintf(buffer, " Malloc: %d\n Calloc: %d\n Realloc: %d\n Total: %d\n", 
                    malloc_allocation, calloc_allocation, realloc_allocation, total_allocation);
    write(1, buffer, len);

    // Calculate remaning memory in heap aka if there are memory leaks
    // Note the below is a place holder - realloc could act as free therefore not enough. 
    int potential_leaks_counts = malloc_count + calloc_count + realloc_count - free_count;

    int potential_leaks_bytes;

    // Change output colour based on leak detection. 

    if (potential_leaks_counts > 0){
        // Red colour.
        write(1, "\033[1;31m", 7);

            len = sprintf(buffer, "\n=====================================");
            write(1, buffer, len);
            len = sprintf(buffer, "\n       Memory Leaks Detected", 
                                    potential_leaks_counts > 0 ? potential_leaks_counts : 0);
            write(1, buffer, len);
            len = sprintf(buffer, "\n=====================================");
            write(1, buffer, len);

    }else{
        // Green colour.
        write(1, "\033[1;32m]", 7);
        
            len = sprintf(buffer, "\n=====================================");
            write(1, buffer, len);
            len = sprintf(buffer, "\n            No Memory Leaks", 
                                    potential_leaks_counts > 0 ? potential_leaks_counts : 0);
            write(1, buffer, len);
            len = sprintf(buffer, "\n=====================================");
            write(1, buffer, len);
    }

    // Remove colour.
    write(1, "\033[0m]", 4);

}

// Destructor function is called when the shared library (.so) is unloaded.

__attribute__((destructor))
static void finalise_memory_hooks(void)
{
    DEBUG("\nHeapHeaver is finalising...");
    heap_report();
    // Print remaining nodes via print_nodes();
}


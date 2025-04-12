#define _GNU_SOURCE // for dlsym with RTLD_NEXT
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include "memory_hooks.h"

// Function pointers.

void*(*original_malloc)(size_t size);

void*(*original_calloc)(size_t nmemb, size_t size);

void*(*original_realloc)(void *ptr, size_t size);

void(*original_free)(void *ptr);

/// Later on within constructor (aka first thing done when .so LD_PRELOADED enables hook loading)

int main(void)
{
    original_malloc = dlsym(RTLD_NEXT, "malloc");
    if(!original_malloc)
    {
        write(2, "Err: Could not find original malloc\n", 37);
        exit(1);
    }

    original_calloc = dlsym(RTLD_NEXT, "calloc");
    if(!original_calloc)
    {
        write(2, "Err: Could not find original calloc\n", 37);
        exit(1);
    }

    original_realloc = dlsym(RTLD_NEXT, "realloc");
    if(!original_realloc)
    {
        write(2, "Err: Could not find original realloc\n", 38);
        exit(1);
    }

    original_free = dlsym(RTLD_NEXT, "free");
    if(!original_free)
    {
        write(2, "Err: Could not find original free\n", 35);
        exit(1);
    }


    // test to see if capture of orignal dynamic memory functions works

    int * ptrInt = original_malloc(10);
    if(ptrInt == NULL)
    {
        printf("NULL ptr retuned");

    }else{
        printf("Memory allocated at address %p\n", ptrInt);
        free(ptrInt);
    }

    printf("\nEnd\n");
    return 0;

}


// static void init_hooks(void){ what you see above}

// constructor / setup
// init_hooks()


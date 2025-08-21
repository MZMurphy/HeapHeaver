#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "../lib/node.h"
#include "../lib/memory_hooks.h"
#include "../lib/memory_bookkeeping.h"

// our versions of function pointers in memory_bookkeeping.c
void* (*original_malloc)(size_t size) = malloc;
void (*original_free)(void *ptr) = free;


void print_result(const char* test_name, int success)
{
    printf("[%s] %s\n", success ? "PASSED" : "FAILED", test_name);
}


int main(void)
{
    printf("=== Bookkeeping Test ===\n\n");

    // Add and search nodes.
    printf("1. Testing add_node() and search_nodes()\n");
    void* ptr1 = (void*)0x12345678;
    void* ptr2 = (void*)0x87654321;

    add_node(ptr1, 100);
    add_node(ptr2, 200);

    MemoryNode* found1 = search_nodes((void*)ptr1);
    MemoryNode* found2 = search_nodes((void*)ptr2);
    void* notFound = search_nodes((void*)0x11111111);

    int addAndSearchTest = (found1 != NULL) && (found2 != NULL) && (notFound == NULL);
    print_result("Add and search nodes", addAndSearchTest);


    printf("\nAfter adding nodes:\n");
    print_nodes();

    // Modify nodes.

    printf("2. Testing modify_node()\n");
    void* newPtr = (void*)0x22222222;

    int modifySuccess = modify_node(ptr1, newPtr, 150);

    MemoryNode* foundMod = search_nodes((void*)newPtr);
    MemoryNode* foundOg = search_nodes((void*)ptr1);

    int modifyTest = (modifySuccess == 1 && foundMod != NULL && foundOg == NULL && foundMod->size == 150);
    print_result("Modify memory allocation", modifyTest);

    printf("\nAfter modifying nodes:\n");
    print_nodes();

    printf("3. Testing remove_node()\n");
    int removeSuccess = remove_node(ptr2);

    MemoryNode* foundAfterRemoved = search_nodes(ptr2);
    int removeTest = (removeSuccess == 1 && foundAfterRemoved == NULL);
    print_result("Remove node", removeTest);

    printf("\nAfter removing node:\n");
    print_nodes();

    // Cleanup testing of remaining nodes

    printf("4. Testing clean_memory_bookkeeping()\n");
    clean_memory_bookkeeping();

    printf("\nAfter cleaning:\n");
    print_nodes();

    




}
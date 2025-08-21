#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <memory_hooks.h>
#include <memory_bookkeeping.h>

// Entry point of linked list.
static MemoryNode* memory_bookkeeping = NULL;

// Function to create a node.
static MemoryNode* create_node(void* address, size_t size)
{
    MemoryNode* node = (MemoryNode*)original_malloc(sizeof(MemoryNode));
    if (node == NULL){
        write(2, "Error: Node allocation failed!", 31);
        return NULL;
    }

    node->address = address;
    node->size = size;
    node->next = NULL;
    return node;
} 

// Function to add new memory node to the list
void add_node(void* address, size_t size)
{
    if(address == NULL){
        return;
    }

    // create new node
    MemoryNode* new_node = create_node(address, size);
    if(new_node == NULL){
        return; 
    }

    // Add node to begging of list as it's faster
    new_node->next = memory_bookkeeping;
    memory_bookkeeping = new_node;
}

// Function to remove node

int remove_node(void* address)
{
    if (address == NULL || memory_bookkeeping == NULL){
        return 0;
    }

    // If node is head node...
    if(memory_bookkeeping->address == address){
        MemoryNode* temp = memory_bookkeeping;
        memory_bookkeeping = memory_bookkeeping->next;
        original_free(temp);
        return 1;
    }

    // Search for specified node.
    MemoryNode* current = memory_bookkeeping;
    while(current->next != NULL && current->next->address != address){
        current = current -> next;
    }

    // If found remove it.
    if(current->next != NULL){
        MemoryNode* temp = current->next;
        current->next = temp->next;
        original_free(temp);
        return 1;
    }

    // Not found.
    return 0; 

}

// Function to search and return node
MemoryNode* search_nodes(void* address)
{
    if(address == NULL || memory_bookkeeping == NULL){
        return NULL;
    }

    // Search for node
    MemoryNode* current = memory_bookkeeping;
    while(current != NULL){
        if(current->address == address){
            // Return node
            return current; 
        }
    
        // Keep traversing
        current = current->next; 
        
    }
    // Else return NULL for not found
    return NULL; 
}


void print_nodes(void)
{
    char buffer[1024];
    int len;

    if(memory_bookkeeping == NULL)
    {
        len = sprintf(buffer, "No nodes remaining.\n");
        write(1, buffer, len);
        return;
    }

    MemoryNode* current = memory_bookkeeping;
    int count = 0;

    while (current != NULL){
        len = sprintf(buffer, "[%d] Address: %p, Size: %zu bytes\n",
                        count++, current->address, current->size);
        write(1, buffer, len);
        current = current -> next;
    }

    write(1, "End.\n\n", 7);
}

int modify_node(void* old_address, void* new_address, size_t new_size)
{
    if(old_address == NULL){return 0;}

    MemoryNode* node = search_nodes((void*)old_address);

    // If found, update the node.
    if(node != NULL){
        node->address = new_address;
        node->size = new_size;
        return 1;
    }

    return 0; // Not found. 
}

// Clean up function??? not sure

void clean_memory_bookkeeping(void)
{
    MemoryNode* current = memory_bookkeeping;
    MemoryNode* next;

    while(current !=NULL){
        next = current->next;
        original_free(current);
        current = next;
    }

    memory_bookkeeping = NULL;
}
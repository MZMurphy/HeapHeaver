#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
    char * ptr1 = (char*)malloc(10);
    int * ptr2 = (int*)calloc(2, 2);

    free(ptr2);

    char * ptr3 = (char*)realloc(ptr1, 15);

    free(ptr3);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int 
main(void)
{
    char * ptr1 = (char*)malloc(10);
    if(ptr1 == NULL)
    {
        printf("\nNull return.");
    }else{
        printf("\nMalloc success.");
    }
}
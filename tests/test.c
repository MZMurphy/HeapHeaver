#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char * ptr1 = (char*)malloc(10);
    if (ptr1 == NULL)
    {
        write(1, "\nNull returned.", 14);
    }else{
        write(1, "\nMalloc success.", 17);
    }

    free(ptr1);

}
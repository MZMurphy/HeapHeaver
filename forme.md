

## Build executbale with .h / personla library dependencies

Example you may need to modify:
`gcc -I./lib ./src/heap_heaver.c ./src/memory_hooks.c -o ./build/heap_heaver.out -g -ggdb`
- Use flag -I to denote "looking in this place for dependencies"
- Make sure you have the depencies `#include`ed in your files
    - .h files repliant on .c functions for declarations must also have their .c explicitly linked






## Left As:
Created `hook_malloc()` to see if calling would print. It does. 

What next? I dont seem to be able to use `malloc()` explicitly. Not sure why. I assume confusion with my version VS the original as I have not used LD_PRELOAD yet. 


Next? 

1.Get hooks up and going <-- figure out issue
2.Use LD_PRELOAD to get working on excutables.

... 
 
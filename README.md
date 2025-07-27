# HeapHeaver 
HeapHeaver is my attempt to mimic (and improve!) Valgrind's Memcheck feature.

# Description

Something that has always mistified me is Valgrind's refusal to specify *which* ALLOCS and DEALLOCS have been called. The total is useful, but it's not specific! At least not enough for me. 

# How To Use

1. Compile memory_hooks.c 
`gcc -I./lib -c ./src/memory_hooks.c -o ./build/memory_hooks.out -fPIC -g -ggdb`

2. Compile heap_heaver
`gcc -I./lib -c ./src/heap_heaver.c -o ./build/heap_heaver.out -fPIC -g -ggdb`

3. Link both binaries / object files together into a shared library (.so) with dynamic loading
`gcc -shared -o ./build/heap_heaver.so ./build/memory_hooks.out ./build/heap_heaver.out -ldl`

4. Run your test binary with the shared library (.so) preloaded 
` LD_PRELOAD=./build/heap_heaver.so ./tests/test.out `

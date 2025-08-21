# HeapHeaver 
HeapHeaver is my attempt to mimic (and improve!) Valgrind's Memcheck feature.

# Description

Something that has always mistified me is Valgrind's refusal to specify *which* ALLOCS and DEALLOCS have been called. The total is useful, but it's not specific! At least not enough for me. 

# How To Use

# Build Instructions

## HeapHeaver

```bash
# 1. Compile memory_hooks.c
gcc -I./lib -c ./src/memory_hooks.c -o ./build/memory_hooks.o -fPIC -g -ggdb

# 2. Compile heap_heaver.c
gcc -I./lib -c ./src/heap_heaver.c -o ./build/heap_heaver.o -fPIC -g -ggdb

# 3. Link into a shared library (.so)
gcc -shared -o ./build/libheap_heaver.so ./build/memory_hooks.o ./build/heap_heaver.o -ldl

# 4. Run target binary with heap_heaver.so (shared library) preloaded.
 LD_PRELOAD=./build/heap_heaver.so ./tests/test.out
```
## Tests
```bash
# 1. Compile memory_bookkeeping_test, which is isolated from the rest of HeapHeaver
`gcc -I./lib -o ./tests/memory_bookkeping_test ./tests/memory_bookkeping_test.c ./src/memory_bookkeeping.c`

# 2. Run bookkeeping test binary
`./tests/memory_bookkeping_test`
```

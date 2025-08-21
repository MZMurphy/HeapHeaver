
# Bookkeeping implicitly included and updated via .h includes
# 1. Compile memory_hooks.c
gcc -I./lib -c ./src/memory_hooks.c -o ./build/memory_hooks.o -fPIC -g -ggdb

# 2. Compile heap_heaver.c
gcc -I./lib -c ./src/heap_heaver.c -o ./build/heap_heaver.o -fPIC -g -ggdb

# 3. Link into a shared library (.so)
gcc -shared -o ./build/libheap_heaver.so ./build/memory_hooks.o ./build/heap_heaver.o -ldl

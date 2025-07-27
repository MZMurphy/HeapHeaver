#ifndef LOG_H
#define LOG_H
#include <stdio.h>


#if DEBUG_PRINT == 1
#define DEBUG(str) write(1, str, sizeof(str) -1 ) // DEBUG for string literals print, removes null terminator.
#else
#define DEBUG(str) do {} while(0); 
#endif // DEBUG

#endif // LOG_H
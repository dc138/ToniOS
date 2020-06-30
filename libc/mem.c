/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    lib/mem.c:
    Defines a way for the kernel to perform memory functions 

*/

#include <libc/mem.h>

/*
_________________________

    Public Kernel API
_________________________

*/

/* Used to copy a number of bytes from source to destination */
void memcpy(char* source, char* dest, int bytes) {
    for (int i = 0; i < bytes; i++) {
        *(dest + i) = *(source + i);
    }
}
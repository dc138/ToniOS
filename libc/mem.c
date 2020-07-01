/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    lib/mem.c:
    Defines a way for the kernel to perform memory functions 

*/

#include <libc/mem.h>
#include <libc/type.h>

/* Used to copy a number of bytes from source to destination */
void memcpy(char* source, char* dest, size_t bytes) {
    for (uint32_t i = 0; i < bytes; i++) {
        *(dest + i) = *(source + i);
    }
}

/* Used to set an area of memory to a fixed value */
void memset(char* dest, char val, size_t lenght) {
    for (uint32_t i = 0; i < lenght; i++) {
        *(dest + i) = val;
    }
}

/* Test wether two areas of memory are similar */
int memcmp(char* source, char* dest, size_t lenght) {
    for (size_t i = 0; i < lenght; i++, source++, dest++) {
        if (*source < *dest) {
            return -1;
        } else if (*source > *dest) {
            return 1;
        }
    }

    return 0;
}

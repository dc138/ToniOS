/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    lib/mem.c:
    Defines a way for the kernel to perform memory functions 

*/

#include <libc/mem.h>

/* Used to copy a number of bytes from source to destination */
void memcpy(uint8_t* source, uint8_t* dest, uint32_t bytes) {
    for (uint32_t i = 0; i < bytes; i++) {
        *(dest + i) = *(source + i);
    }
}

/* Used to set an area of memory to a fixed value */
void memset(uint8_t* dest, uint8_t val, uint32_t lenght) {
    for (uint32_t i = 0; i < lenght; i++) {
        *(dest + i) = val;
    }
}

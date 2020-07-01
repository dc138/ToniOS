/* 
    MIT License
    (c) Antonio de Haro 2020

    See attached LICENSE file for more info

    libc/type.h:
    TODO 

*/

#ifndef LIBC_TYPE
#define LIBC_TYPE

#include <stdint.h>

#define low16(val) (uint16_t)((val)&0xFFFF)
#define high16(val) (uint16_t)(((val) >> 16) & 0xFFFF)

#define low8(val) (uint16_t)((val)&0xFF)
#define high8(val) (uint16_t)(((val) >> 8) & 0xFF)

#define UNUSED(x) (void)(x)
#define ASM(...) __asm__ __volatile__(__VA_ARGS__)

#endif
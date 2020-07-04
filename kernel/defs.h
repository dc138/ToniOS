/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    kernel/defs.h
    Implements several useful defines used in this project.

*/

#ifndef KERNEL_DEFS
#define KERNEL_DEFS

#define low16(val) (uint16_t)((val)&0xFFFF)
#define high16(val) (uint16_t)(((val) >> 16) & 0xFFFF)

#define low8(val) (uint16_t)((val)&0xFF)
#define high8(val) (uint16_t)(((val) >> 8) & 0xFF)

#define UNUSED(x) (void)(x)
#define ASM(...) __asm__ __volatile__(__VA_ARGS__)

#define CLI() ASM("cli")
#define HLT() ASM("hlt")

#endif
/* 
    MIT License
    (c) Antonio de Haro 2020

    See attached LICENSE file for more info

    kernel/kernel.h:
    Defines rutines Kernel that other files should have access to.

*/

#ifndef KERNEL_KERNEL
#define KERNEL_KERNEL

#include <libc/type.h>

/* Describes wether the OS is currently running */
static bool running = true;

void input(char* str);

#endif
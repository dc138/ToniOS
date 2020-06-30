/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.


    kernel/entry.c:
    Kernel entry file 

*/

#include <drivers/screen.h>

void entry() {  // Defines the entry point for the kernel
    print("Kernel started!");
    return;
}
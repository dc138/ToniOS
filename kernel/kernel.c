/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    kernel/entry.c:
    Kernel entry file 

*/

#include <drivers/screen.h>
#include <libc/str.h>

void entry() {  // Defines the entry point for the kernel
    clear();

    print("\n\033F0Wellcome to \033A0ToniOS\033F0!\n\n\n");
    print("\03370$ ");

    __asm__ __volatile__("hlt");  // Temporary
}

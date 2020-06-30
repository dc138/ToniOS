/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    kernel/entry.c:
    Kernel entry file 

*/

#include <drivers/screen.h>

void entry() {  // Defines the entry point for the kernel
    clear();

    set_color(COLOR(LIGHT_GREY, BLACK));
    print("\nWellcome to ");

    set_color(COLOR(WHITE, BLACK));
    print("ToniOS");

    set_color(COLOR(LIGHT_GREY, BLACK));
    print("!");

    set_color(COLOR(WHITE, BLACK));
    print("\nTest.");

    __asm__("hlt");  // Temporary
}
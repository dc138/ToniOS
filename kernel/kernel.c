/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    kernel/entry.c:
    Kernel entry file 

*/

#include <cpu/idt.h>
#include <cpu/isr.h>
#include <cpu/timer.h>
#include <drivers/keyboard.h>
#include <drivers/screen.h>
#include <libc/str.h>
#include <libc/type.h>

void entry() {  // Defines the entry point for the kernel
    isr_install();
    ASM("sti");

    init_timer(50);
    init_keyboard();

    clear();

    print("\n  \033F0Wellcome to \033A0ToniOS\033F0!\n\n");
    print("\03370$ ");

    STAY();  // Cant halt because that will mess up the interrupt handling, instead just run an infinite loop
}

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
#include <kernel/kernel.h>
#include <libc/str.h>
#include <libc/type.h>

/* Defines the entry point for the kernel */
void entry() {
    isr_install();  // Setup the interrupt service
    irq_install();  // Setup the user interupt request callbacks (Keyboard and timer)

    clear();

    print("\n  \033F0Wellcome to \033A0ToniOS\033F0!\n\n");
    print("\03370$ ");

    while (running) {
    }  // Wait here asyncronously handling interrupts until needed.
}

/* This function will be called every time some process whants the kernel to process something */
void input(char* str) {
    if (strcmp(str, "HELP") == 0) {
        print("\03370Available commands are: HELP, ABOUT and QUIT.\n");
    } else if (strcmp(str, "ABOUT") == 0) {
        print("\03370Currently running \033A0ToniOS \03370Kernel version \033A0V1.0 RELASE\03370.\n");
    } else if (strcmp(str, "QUIT") == 0) {
        print("\03370Shutting down, goodbye.");
        running = false;
        return;
    } else {
        print("\033C0Unknown command, please do HELP to see a list of possible commands.\n");
    }

    print("\03370$ ");
}

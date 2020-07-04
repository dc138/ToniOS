/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    libc/sleep.c:
    Provides a way for processes to sleep

*/

#include <libc/sleep.h>
#include <kernel/defs.h>
#include <cpu/timer.h>

/* 
    Sleep for a given amount of milisconds. Note how we
    HLT without disabling interrupts to allow the CPU to
    still process.
*/
void sleep(uint32_t ms) {
    reset_timer();

    while (get_tick() != ms) {
        HLT();
    }
}

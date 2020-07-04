/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    cpu/timer.h:
    TODO

*/

#ifndef TIMER_H
#define TIMER_H

#include <libc/type.h>

/* Initialise the timer with the timer callback function */
void init_timer(uint32_t freq);
void reset_timer();
uint32_t get_tick();
void stop_timer();

#endif

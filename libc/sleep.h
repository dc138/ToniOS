/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    libc/sleep.h:
    Provides a way for processes to sleep

*/

#ifndef LIBC_SLEEP
#define LIBc_SLEEP

#include <libc/type.h>

/* Sleep a given amount of miliseconds */
void sleep(uint32_t ms);

#endif

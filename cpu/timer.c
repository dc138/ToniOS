/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    cpu/timer.c:
    TODO

*/

#include <cpu/isr.h>
#include <cpu/ports.h>
#include <cpu/timer.h>
#include <drivers/screen.h>
#include <kernel/defs.h>
#include <libc/str.h>
#include <libc/type.h>

static uint32_t tick = 0;

/* This will be called on each timer interrupt once the init_timer function has been setup */
static void timer_callback(registers_t regs) {
    UNUSED(regs);
    tick++;
}

/* Initialise the timer with the timer callback function */
void init_timer(uint32_t freq) {
    register_interrupt_handler(IRQ0, timer_callback);  // Install the function

    // Get the PIT value: hardware clock at 1193180 Hz
    uint32_t divisor = 1193180 / freq;
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    // Send the command
    byte_out(0x43, 0x36);
    byte_out(0x40, low);
    byte_out(0x40, high);
}

/* Reset the tick */
void reset_timer() {
    tick = 0;
}

/* Get the current tick */
uint32_t get_tick() {
    return tick;
}

/* Stop the timer */
void stop_timer() {
    register_interrupt_handler(IRQ0, NULL);

    // Send the command
    byte_out(0x43, 0x36);
    byte_out(0x40, 0x0);
    byte_out(0x40, 0x0);
}

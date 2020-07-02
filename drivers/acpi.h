/* 
    MIT License
    (c) Antonio de Haro 2020

    See attached LICENSE file for more info

    drivers/acpi.h:
    Header file for the ACPI driver

*/

#ifndef DRIVERS_ACPI
#define DRIVERS_ACPI

#include <cpu/ports.h>
#include <cpu/timer.h>
#include <drivers/screen.h>
#include <libc/mem.h>
#include <libc/type.h>

/* Initialises the ACPI */
int32_t acpi_init(void);

/* Instructs the power controller to invoke a system shutdown */
void acpi_poweroff();

#endif

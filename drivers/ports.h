/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    drivers/ports.h:
    Main kernel API port divers prototypes 

*/

#ifndef DRIVER_PORTS
#define DRIVER_PORTS

/* Output rutines */
void byte_out(unsigned short port, unsigned char data);
void word_out(unsigned short port, unsigned short data);

/* Input rutines */
unsigned char byte_in(unsigned short port);
unsigned short word_in(unsigned short port);

#endif

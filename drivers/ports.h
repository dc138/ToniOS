#ifndef DRIVER_PORTS
#define DRIVER_PORTS

/* Output rutines */
void byte_out(unsigned short port, unsigned char data);
void word_out(unsigned short port, unsigned short data);

/* Input rutines */
unsigned char byte_in(unsigned short port);
unsigned short word_in(unsigned short port);

#endif
/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    lib/mem.h:
    Main kernel memory operations API prototypes 

*/

#ifndef LIBC_MEM
#define LIBC_MEM

#include <libc/type.h>

/* Memory manipulation rutines */
void memcpy(uint8_t* source, uint8_t* dest, uint32_t bytes);
void memset(uint8_t* dest, uint8_t val, uint32_t lenght);

#endif

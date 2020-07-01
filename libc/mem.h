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
void memcpy(char* source, char* dest, size_t bytes);
void memset(char* dest, char val, size_t lenght);
int memcmp(char* source, char* dest, size_t lenght);

#endif

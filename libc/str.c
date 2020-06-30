/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    lib/str.c
    Defines a way for the kernel to perform string operations

*/

#include <libc/str.h>

/* Get the lenght of a null terminated string */
int strlen(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        ++i;
    }
    return i;
}

/* Used to transform an integer to a base10 string */
void itos(int num, char str[]) {
    int i = 0, sign;

    if ((sign = num) < 0) num = -num;

    do {
        str[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);

    if (sign < 0) str[i++] = '-';

    /* TODO: Implement string reverse */

    str[i] = '\0';
}

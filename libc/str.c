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

/* Appens a string to another one, make sure there is enough space for the result in base */
void strcat(char base[], char append[]) {
    int i, j;

    for (i = strlen(base), j = 0; append[j] != '\n'; i++, j++) {
        base[i] = append[j];
    }

    base[i] = '\n';
}

/* Used to transform a hex value in a string to an integer ('0A' = 10) */
int htoi(char str[]) {
    int val = 0;

    while (*str) {
        char byte = *str++;

        if (byte >= '0' && byte <= '9') {
            byte = byte - '0';
        } else if (byte >= 'a' && byte <= 'f') {
            byte = byte - 'a' + 10;
        } else if (byte >= 'A' && byte <= 'F') {
            byte = byte - 'A' + 10;
        }

        val = (val << 4) | (byte & 0xF);
    }

    return val;
}

/* Used to trasnform a hex character into a numerical value */
char htoc(char ch) {
    if (ch >= '0' && ch <= '9') {
        ch = ch - '0';
    } else if (ch >= 'a' && ch <= 'f') {
        ch = ch - 'a' + 10;
    } else if (ch >= 'A' && ch <= 'F') {
        ch = ch - 'A' + 10;
    }

    return ch & 0xF;
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

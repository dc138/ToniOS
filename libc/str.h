/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    lib/str.c
    Main Kernel string operations prototypes

*/

#ifndef LIBC_STR
#define LIBC_STR

/* String rutines */
int strlen(char str[]);
void strcat(char str1[], char str2[]);

void itos(int num, char str[]);
char htoc(char ch);
int htoi(char str[]);

#endif

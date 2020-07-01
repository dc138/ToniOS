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
void reverse(char s[]);
void strcat(char str1[], char str2[]);
int strcmp(char str1[], char str2[]);

void itos(int num, char str[]);
char htoc(char ch);
int htoi(char str[]);

void backspace(char str[]);
void append(char str[], char val);

#endif

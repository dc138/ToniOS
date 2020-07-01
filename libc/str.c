/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    lib/str.c
    Defines a way for the kernel to perform string operations

*/

#include <libc/str.h>
#include <libc/type.h>

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

/* Used to compare two if two string, returns 0 if they are the same */
int strcmp(char str1[], char str2[]) {
    uint32_t i;

    for (i = 0; str1[i] == str2[i]; i++) {
        if (str1[i] == '\0') return 0;
    }

    return str1[i] - str2[i];
}

/* Used to reverse a string */
void reverse(char s[]) {
    for (int i = 0, j = strlen(s) - 1, c; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
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
    str[i] = '\0';  // Make sure its null terminated

    reverse(str);
}

/* Used to remove a character from a string */
void backspace(char str[]) {
    str[strlen(str) - 1] = '\0';
}

/* Used to append a character to a string, make sure that there is enough space for the new string */
void append(char str[], char val) {
    str[strlen(str)] = val;
    str[strlen(str) + 1] = '\0';
}

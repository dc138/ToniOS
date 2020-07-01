/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info.

    drivers/screen.c:
    Defines a way for the kernel to more easily print to the screen 

*/

#include <cpu/ports.h>
#include <drivers/screen.h>
#include <libc/mem.h>
#include <libc/str.h>

/* Simple arithmetic calculations to convert 1d arrays to 2d */
#define OFFSET(col, row) (2 * ((row)*MAX_COLS + (col)))
#define OFFSET_ROW(offset) ((offset) / (2 * MAX_COLS))
#define OFFSET_COL(offset) (((offset) - (OFFSET_ROW(offset) * 2 * MAX_COLS)) / 2)

/* The currrent color used to write to the screen */
static char current_color = COLOR(WHITE, BLACK);
static char last_char = ' ';
static char count = 0;

/* Gets the current cursor's position */
static inline int get_cursor() {
    byte_out(VIDEO_CTRL, 14);
    int offset = byte_in(VIDEO_DATA) << 8;

    byte_out(VIDEO_CTRL, 15);
    offset += byte_in(VIDEO_DATA);

    return offset * 2;
}

/* Sets the current cursor's position */
static inline void set_cursor(int offset) {
    offset /= 2;

    byte_out(VIDEO_CTRL, 14);
    byte_out(VIDEO_DATA, (unsigned char)(offset >> 8));

    byte_out(VIDEO_CTRL, 15);
    byte_out(VIDEO_DATA, (unsigned char)(offset & 0xff));
}

/* Prints a single character and returns the offset to the next one. */
static int char_print(char c, int col, int row) {
    unsigned char *video = (unsigned char *)VIDEO_ADDRESS;

    if (col >= MAX_COLS || row >= MAX_ROWS) {
        video[2 * (MAX_COLS) * (MAX_ROWS)-2] = 'E';
        video[2 * (MAX_COLS) * (MAX_ROWS)-1] = COLOR(RED, WHITE);
        return OFFSET(col, row);
    }

    int offset = OFFSET(col, row);

    if (c == '\n') {
        row = OFFSET_ROW(offset);
        offset = OFFSET(0, row + 1);
    } else if (c == '\033') {
        count = 2;
    } else if (count == 2) {  // First color char, indicates foreground
        last_char = c;
        count--;
    } else if (count == 1) {  // Sencond color char, indicates background
        current_color = COLOR(htoc(last_char), htoc(c));
        count--;
    } else if (c == 0x08) {  // Backspace
        video[offset] = ' ';
        video[offset + 1] = current_color;
    } else {
        video[offset] = c;
        video[offset + 1] = current_color;
        offset += 2;
    }

    /* Check if the offset is over screen size and scroll */
    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        for (int i = 1; i < MAX_ROWS; i++)
            memcpy(OFFSET(0, i) + (char *)VIDEO_ADDRESS,
                   OFFSET(0, i - 1) + (char *)VIDEO_ADDRESS,
                   MAX_COLS * 2);

        /* Blank last line */
        char *last_line = (char *)OFFSET(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
        for (int i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

        offset -= 2 * MAX_COLS;
    }

    set_cursor(offset);
    return offset;
}

/* Clears the screen with blank characters */
void clear() {
    char *screen = (char *)VIDEO_ADDRESS;

    for (int i = 0; i < MAX_COLS * MAX_ROWS; i++) {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = COLOR(WHITE, BLACK);
    }

    set_cursor(OFFSET(0, 0));
}

/* 
    Prints a string on a specified location, if colum or row are negative, 
    the character will be printed on the cursor. To use color formatting 
    use the escape secuence \033BF, where B and F are hex values and represent 
    the background and foreground color of the following text.
*/
void print_at(char *message, int col, int row) {
    int offset;

    if (col >= 0 && row >= 0) {
        offset = OFFSET(col, row);
    } else {
        offset = get_cursor();
        row = OFFSET_ROW(offset);
        col = OFFSET_COL(offset);
    }

    for (int i = 0; message[i] != 0; i++) {
        offset = char_print(message[i], col, row);

        row = OFFSET_ROW(offset);
        col = OFFSET_COL(offset);
    }
}

/* Prints a string on the cursor's position */
void print(char *message) {
    print_at(message, -1, -1);
}

/* Removes the last character and returns the cursor one position back */
void print_backspace() {
    int offset = get_cursor() - 2;
    int row = OFFSET_ROW(offset);
    int col = OFFSET_COL(offset);
    char_print(0x08, col, row);
}

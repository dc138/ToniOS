#include <drivers/ports.h>
#include <drivers/screen.h>

/*
_________________________

    Private functions
_________________________

*/

/* Simple arithmetic calculations to convert 1d arrays to 2d */
#define OFFSET(col, row) (2 * (row * MAX_COLS + col))
#define OFFSET_ROW(offset) (offset / (2 * MAX_COLS))
#define OFFSET_COL(offset) ((offset - (OFFSET_ROW(offset) * 2 * MAX_COLS)) / 2)

/* Gets the current cursor's position */
static inline int get_cursor_offset() {
    byte_out(VIDEO_CTRL, 14);
    int offset = byte_in(VIDEO_DATA) << 8;

    byte_out(VIDEO_CTRL, 15);
    offset += byte_in(VIDEO_DATA);

    return offset * 2;
}

/* Sets the current cursor's position */
static inline void set_cursor_offset(int offset) {
    offset /= 2;

    byte_out(VIDEO_CTRL, 14);
    byte_out(VIDEO_DATA, (unsigned char)(offset >> 8));

    byte_out(VIDEO_CTRL, 15);
    byte_out(VIDEO_DATA, (unsigned char)(offset & 0xff));
}

/* Prints a single character and returns the offset to the next one */
static int charprint(char c, int col, int row, char attr) {
    unsigned char *video = (unsigned char *)VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    if (col >= MAX_COLS || row >= MAX_ROWS) {
        video[2 * (MAX_COLS) * (MAX_ROWS)-2] = 'E';
        video[2 * (MAX_COLS) * (MAX_ROWS)-1] = RED_ON_WHITE;
        return OFFSET(col, row);
    }

    int offset = OFFSET(col, row);

    if (c == '\n') {
        row = OFFSET_ROW(offset);
        offset = OFFSET(0, row + 1);
    } else {
        video[offset] = c;
        video[offset + 1] = attr;
        offset += 2;
    }

    set_cursor_offset(offset);
    return offset;
}

/*
_________________________

    Public Kernel API
_________________________

*/

/* Clears the screen with blank characters */
void clear() {
    char *screen = (char *)VIDEO_ADDRESS;

    for (int i = 0; i < MAX_COLS * MAX_ROWS; i++) {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = WHITE_ON_BLACK;
    }

    set_cursor_offset(OFFSET(0, 0));
}

/* 
   Prints a string on a specified location, if colum or
   row are negative, the character will be printed on 
   the cursor
*/
void print_at(char *message, int col, int row) {
    int offset;

    if (col >= 0 && row >= 0) {
        offset = OFFSET(col, row);
    } else {
        offset = get_cursor_offset();
        row = OFFSET_ROW(offset);
        col = OFFSET_COL(offset);
    }

    for (int i = 0; message[i] != 0; i++) {
        offset = charprint(message[i], col, row, WHITE_ON_BLACK);

        row = OFFSET_ROW(offset);
        col = OFFSET_COL(offset);
    }
}

/* Prints a string on the cursor's position */
void print(char *message) {
    print_at(message, -1, -1);
}

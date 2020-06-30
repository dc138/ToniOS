/* 
    MIT License
    (c) Antonio de Haro, 2020

    See attached LICENSE file for more info

    drivers/screen.h:
    Main kernel API screen divers prototypes 

*/

#ifndef DRIVER_SCREEN
#define DRIVER_SCREEN

/* Screen IO ports */
#define VIDEO_ADDRESS 0xb8000
#define VIDEO_CTRL 0x3d4
#define VIDEO_DATA 0x3d5

/* Screen characteristics */
#define MAX_ROWS 25
#define MAX_COLS 80

/* Generate a color constant from a background and foreground */
#define COLOR(fg, bg) (fg | bg << 4)

/* Color constants */
enum vga_color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15,
};

/* Kernel interface API */
void set_color(char c);
char get_color();

void clear();

void print_at(char* message, int col, int row);
void print(char* message);

#endif

/* 
    MIT License
    (c) Antonio de Haro 2020

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

/* Color values for reference, see screen.c:print() for more info */
#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GREY 0x7
#define DARK_GREY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN 0xB
#define LIGHT_RED 0xC
#define LIGHT_MAGENTA 0xD
#define LIGHT_BROWN 0xE
#define WHITE 0xF

/* Kernel interface API */
void clear();

void print_at(char* message, int col, int row);
void print(char* message);

#endif

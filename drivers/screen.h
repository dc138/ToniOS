#ifndef DRIVER_SCREEN
#define DRIVER_SCREEN

/* Screen IO ports */
#define VIDEO_ADDRESS 0xb8000
#define VIDEO_CTRL 0x3d4
#define VIDEO_DATA 0x3d5

/* Screen characteristics */
#define MAX_ROWS 25
#define MAX_COLS 80

/* Color constants */
#define WHITE_ON_BLACK 0x0f
#define GRAY_ON_BLACK
#define GREEN_ON_BLACK
#define RED_ON_WHITE 0xf4

/* Kernel interface API */
void clear();

void print_at(char* message, int col, int row);
void print(char* message);

#endif
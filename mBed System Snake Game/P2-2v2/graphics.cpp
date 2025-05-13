// ============================================
// The Graphics file
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "graphics.h"
#include "globals.h"
#include "snake.h"


#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define LGREY 0xBFBFBF
#define DGREY 0x5F5F5F
#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define ORANGE 0xFFA500
#define PURPLE 0xA020F0
#define LBLUE 0x05F7D1

#include <stdint.h>


// 2035TODO
// You should create your own sprite, but feel free to use this one while setting up your game!
const char* fruit_img =
    "000BG000"
    "000B0000"
    "0RRRRRR0"
    "RRRRRRRR"
    "RRRRRRRR"
    "RRRRRRRR"
    "0RRRRRR0"
    "00RRRR00";
const char* poison_img = 
    "00BBBB00"
    "000GG000"
    "000GG000"
    "000GG000"
    "00GGGG00"
    "0GPGGPG0"
    "0GGGGGG0"
    "00PPPP00";
const char* boost_img = 
    "00000000"
    "0RR00000"
    "R00R0000"
    "00R0Y00Y"
    "0R000YY0"
    "R0000YY0"
    "RRRRY00Y"
    "00000000";
const char* fast_img =
    "00BBB000"
    "0B0B0B0B"
    "B0YYY0B0"
    "0YYYYY00"
    "YYYYYYY0"
    "YYYYYYY0"
    "0YYYYY00"
    "00YYY000";
const char* cloud_img = 
    "G00G00G0"
    "0G0G0G00"
    "00GGG000"
    "00LPL000"
    "PLLLLLP0"
    "LLPLPLL0"
    "0PLLLP00"
    "00PLP000";
const char* death_img = 
    "0WWWWWW0"
    "WWWWWWWW"
    "WW0WW0WW"
    "WWWWWWWW"
    "0WWWWWW0"
    "0W0WW0W0"
    "00W00W00"
    "0WWWWWW0";


// This takes a location (x,y) and const char* as input, and prints a sprite onto the screen
void draw_img(int x, int y, const char* img) {
    int colors[CELL_SIZE*CELL_SIZE];
    for (int i = 0; i < CELL_SIZE*CELL_SIZE; i++)
    {
        switch(img[i]) {
            case 'R':
                colors[i] = RED;
                break;
            case 'Y':
                colors[i] = YELLOW;
                break;
            case 'B':
                colors[i] = BROWN;
                break;
            case 'G':
                colors[i] = GREEN;
                break;
            case 'P':
                colors[i] = PURPLE;
            case '0':
                colors[i] = BLACK;
                break;
            case 'L':
                colors[i] = LBLUE;
                break;
            case 'W':
                colors[i] = WHITE;
                break;
            default:
                colors[i] = BLACK;
                break;
        }
    }
    uLCD.BLIT(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE, colors);
    wait_us(250); // Recovery time!
}

// 2035TODO
void draw_fruit(int x, int y)
{
    // 1. call draw_img OR uLCD.BLIT() to draw a custom sprite that you create
    // 2. OR implement functionality that draws a CELL_SIZExCELL_SIZE square using the uLCD.filled_rectangle function
    // Recall the grid structure of the uLCD screen.
    // CELL_SIZE is 8 in the provided code, and the real size of the uLCD screen is 128x128
    // filled_rectangle takes x1, y1, x2, y2 that define the bounding points (top left, bottom right) of a filled rectangle IN uLCD COORDINATES
    // you must convert the passed in x,y coordinates (which correspond to a 16x16 grid of cells) to uLCD coordinates before drawing the rectangle
    int uLCD_x = x * CELL_SIZE;
    int uLCD_y = y * CELL_SIZE;
    draw_img(x,y, fruit_img);
}

// 2035TODO
// the remainder of these functions should be handled the same way as draw_fruit
void draw_poison(int x, int y)
{
    int uLCD_x = x * CELL_SIZE;
    int uLCD_y = y * CELL_SIZE;
    draw_img(x,y, poison_img);
}

void draw_boost(int x, int y)
{
    int uLCD_x = x * CELL_SIZE;
    int uLCD_y = y * CELL_SIZE;
    draw_img(x,y, boost_img);
}
void draw_fast(int x, int y) {
    int ULCD_x = x * CELL_SIZE;
    int uLCD_y = y * CELL_SIZE;
    draw_img(x,y, fast_img);
}

void draw_cloud(int x, int y) {
    int ULCD_x = x * CELL_SIZE;
    int uLCD_y = y * CELL_SIZE;
    draw_img(x,y, cloud_img);
}

void draw_death(int x, int y) {
    int ULCD_x = x * CELL_SIZE;
    int uLCD_y = y * CELL_SIZE;
    draw_img(x,y, death_img);
}


void draw_snake_body(int x, int y)
{
    int uLCD_x = x * CELL_SIZE;
    int uLCD_y = y * CELL_SIZE;
    if(get_snake()->cloud_active){
        uLCD.filled_rectangle(uLCD_x, uLCD_y, uLCD_x + CELL_SIZE - 1, uLCD_y + CELL_SIZE - 1, BLUE);
    } else{
        uLCD.filled_rectangle(uLCD_x, uLCD_y, uLCD_x + CELL_SIZE - 1, uLCD_y + CELL_SIZE - 1, GREEN);
    }
}

void draw_snake_head(int x, int y)
{
    int uLCD_x = x * CELL_SIZE;
    int uLCD_y = y * CELL_SIZE;
    uLCD.filled_rectangle(uLCD_x, uLCD_y, uLCD_x + CELL_SIZE - 1, uLCD_y + CELL_SIZE - 1, RED);
}


void draw_nothing(int x, int y)
{
    int uLCD_x = x * CELL_SIZE;
    int uLCD_y = y * CELL_SIZE;
    uLCD.filled_rectangle(uLCD_x, uLCD_y, uLCD_x + CELL_SIZE - 1, uLCD_y + CELL_SIZE - 1, BLACK);
}
void draw_jungle_map() {
    //fill background with green and add some "trees"
    uLCD.filled_rectangle(0, 0, 127, 127, 0x228B22); // Jungle green background
    for (int i = 0; i < 8; i++) {
        int x = rand() % 16;
        int y = rand() % 16;
        uLCD.filled_circle(x*8 + 4, y*8 + 4, 3, 0x006400); // Tree (dark green circles)
    }
}

void draw_ocean_map() {
    // fill background with blue and add some "waves"
    uLCD.filled_rectangle(0, 0, 127, 127, 0x1E90FF); // Ocean blue background
    for (int i = 0; i < 8; i++) {
        int x = rand() % 16;
        int y = rand() % 16;
        uLCD.filled_circle(x*8 + 4, y*8 + 4, 3, 0x00BFFF); // Wave (lighter blue circles)
    }
}

void replace_jungle_map(int x, int y) {
    int x_new = x * CELL_SIZE;
    int y_new = y * CELL_SIZE;
    if (rand() % 4 == 0) {
        uLCD.filled_rectangle(x_new, y_new, x_new + CELL_SIZE - 1, y_new + CELL_SIZE - 1, 0x228B22);
        uLCD.filled_circle(x_new+3, y_new+3, 3, 0x006400);
    } else{
        uLCD.filled_rectangle(x_new, y_new, x_new + CELL_SIZE - 1, y_new + CELL_SIZE - 1, 0x228B22);
    }
}

void replace_ocean_map(int x, int y) {
    // fill background with blue and add some "waves"
    int x_new = x * CELL_SIZE;
    int y_new = y * CELL_SIZE;
    if (rand() % 4 == 0) {
        uLCD.filled_rectangle(x_new, y_new, x_new + CELL_SIZE - 1, y_new + CELL_SIZE - 1, 0x1E90FF);
        uLCD.filled_circle(x_new+3, y_new+3, 3, 0x00BFFF);
    } else{
        uLCD.filled_rectangle(x_new, y_new, x_new + CELL_SIZE - 1, y_new + CELL_SIZE - 1, 0x1E90FF);
    }
}


//=================================================================
// The header file for general settings for the project
//
// Copyright 2025 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

#ifndef GLOBAL_H
#define GLOBAL_H
#include "mbed.h"
#include "uLCD_4DGL.h"
#include <math.h>
#include "Nav_Switch.h"

// === [global object] ===
extern uLCD_4DGL uLCD;
extern BufferedSerial pc;           // USB Console output
extern PwmOut speaker;

/*
2035TODO
YOU SHOULD READ THIS BEFORE DOING ANYTHING WITH GRAPHICS.
The game's coordinate system depends on the global CELL_SIZE.
Right now, CELL_SIZE is 8.
The size of the uLCD screen is 128 x 128.
Each Item and Snake body segment takes up one 8x8 'cell' of space
This means that the snake movement, item placement, and basically everything else happens on a 16x16 GRID!!!!! (128 / 8 = 16)
The 'point' structure provides an x and y location on this 16x16 grid of 'cells'
*/
typedef struct {

    // The x-location (left = 0)
    int x;

    // The y-location (top = 0)
    int y;
    
} point;


// === [global settings] ===
#define BACKGROUND_COLOR 0x000000 //black
#define CELL_SIZE 8 // each grid cell occupies 8 pixels, 16x16 grid


// === [define the macro of error handle function] ===
// when the condition (c) is not true, assert the program and show error code
#define ASSERT_P(c,e) do { \
    if(!(c)){ \
        uLCD.printf("\nERROR:%d\n",e); \
        pc.write("\nERROR:%d\n",e); \
        while(1); \
    } \
} while (0)

// === [error code] ===
#define ERROR_NONE 0 // All good in the hood


#endif //GLOBAL_H

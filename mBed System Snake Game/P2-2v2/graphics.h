// ============================================
// The header file for the graphics handling
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "globals.h"

void draw_fruit(int x, int y);
void draw_poison(int x, int y);
void draw_boost(int x, int y);
void draw_cloud(int x, int y);
void draw_fast(int x, int y);
void draw_death(int x, int y);
void draw_snake_body(int x, int y);
void draw_snake_head(int x, int y);
void draw_nothing(int x, int y);
void draw_jungle_map();
void draw_ocean_map();
void replace_jungle_map(int x, int y);
void replace_ocean_map(int x, int y);
 
#endif // GRAPHICS_H
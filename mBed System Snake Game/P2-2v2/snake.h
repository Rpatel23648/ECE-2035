// ============================================
// The header file for Snake class file.
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#ifndef SNAKE_H
#define SNAKE_H

#include "doubly_linked_list.h"
#include "graphics.h"


// Values for snake momentum
#define NONE 0
#define RIGHT 1
#define DOWNWARD 2
#define LEFT 3
#define UPWARD 4
// Add more for advanced features!

// Snake structure
typedef struct {

    // A doubly linked list of SnakeItems
    DLinkedList* snake_list;

    // The snake's score, used for the GameOver Win condition
    int score;

    // The movement direction of the Snake's head
    int direction;

    // The length of the Snake
    int length;

    // The previous posiiton of the Snake's tail node
    // While not intuitive, this will be useful for the grow_snake function!!
    point previous_tail_position;

    // Stores snake boost timer
    int boosted;

    // Store snake FAST FAST FRUIT Effect Timer
    int speed;
    
    //stores if the snake has the cloud cloud fruit active.
    bool cloud_active;
    
    //stores how long the cloud cloud fruit should be active
    int cloud_timer;
    
    //did the snake die?
    bool death_collision;

    // sets up lives system for easy mode and normal.
    int lives;

    //is easy mode active, wrap around
    bool easy_mode;

    //helps restore the map
    int map;

    //hard more shuffle
    bool shuffle;

} Snake;

// SnakeItem structure
// These populate the LLNode->data field
typedef struct{

    // The (x, y) coordinate location of the SnakeItem
    // Refer to globals.h for the definition of the 'point' type
    point position;

    // A function pointer to the draw function for the SnakeItem
    void (*draw)(int, int);

    // Arbitrary extra data for the SnakeItem. Use this for advanced features!!
    void* data;

} SnakeItem;


void snake_init(void);

void grow_snake(void);

Snake* get_snake(void);

void move_snake(void);

void draw_snake(void);

bool check_wall_collision(void);

bool check_self_collision(void);

void reverse_snake();

#endif 
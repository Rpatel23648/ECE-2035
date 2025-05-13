// ============================================
// The header file for the Items class file.
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#ifndef ITEMS_H
#define ITEMS_H

#include "doubly_linked_list.h"
#include "globals.h"

#define FRUIT 0
#define BOOST 1
#define POISON 2
#define FAST_FRUIT 3
#define CLOUD_FRUIT 4
#define DEATH_FRUIT 5


#define NUM_ITEMS 15



typedef struct {
    // DLL of on-screen items
    DLinkedList* items_list; 

    // For use with advanced features
    void* data; 

} Items;


typedef struct {
    // Indicates the "type" of the Item: FRUIT, BOOST, POISON, etc. // Useful for determining how to interact with the object when updating the game state.
    int type;
    
    // Function pointer for drawing the item
    void (*draw)(int, int);

    // Item location in (x,y) coordinates
    point position;
    
    // Arbitrary extra data for the Item. Use this for advanced features!!
    void* data;
    
} Item;

void items_init(void);

Items* get_items(void);

bool check_item_collision();

void replace_item(LLNode* current_item);

void draw_items();

void reshuffle_items();

#endif
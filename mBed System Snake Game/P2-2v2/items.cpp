// ============================================
// The Items class file
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================



#include "items.h"
#include "snake.h"
#include "globals.h"
#include "graphics.h"
#include "doubly_linked_list.h"
#include <cstdlib>
#define FRUITS_NUM 4

Items* items;
bool position_occupied(point position) {
    LLNode* curr = items->items_list->head;
    while(curr != NULL) {
        Item* item = (Item*)curr->data;
        if(item->position.x == position.x && item->position.y == position.y) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}
bool snake_position_occupied(point position) {
    Snake* snake = get_snake();
    LLNode* curr = snake->snake_list->head;
    while(curr != NULL) {
        SnakeItem* item = (SnakeItem*) curr->data;
        if(item->position.x == position.x && item->position.y == position.y){
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// 2035TODO
// This function should initialize the Items struct and populate its linked list with 10 Item.
void items_init(void){
    // locations should be RANDOMLY GENERATED
    // locations should NOT overlap with other items or the snake
    srand(time(0)); //this should help the rand function produce a random number everytime other than the same number over and over
    items = (Items*)malloc(sizeof(Items));
    items->items_list = create_dlinkedlist();
    items->data = NULL;
    
    for (int i = 0; i < FRUITS_NUM; i++) {
        bool valid_position = false;
        point new_position;
        while(!valid_position) {
            new_position.x = rand() % 15;
            new_position.y = rand() % 15;
            if(!position_occupied(new_position) && !snake_position_occupied(new_position)) {
            valid_position = true;
            } 
        }
        Item* new_item = (Item*) malloc(sizeof(Item));
        new_item->type = FRUIT;
        new_item->position = new_position;
        new_item->draw = NULL;
        new_item->data = NULL;
        LLNode* node = create_llnode(new_item);
        insertTail(items->items_list, new_item);
    }


    for (int i = FRUITS_NUM; i < NUM_ITEMS - 1; i++) {
        bool valid_position = false;
        point new_position;
        while(!valid_position) {
            new_position.x = rand() % 16;
            new_position.y = rand() % 16;
            if(!position_occupied(new_position) && !snake_position_occupied(new_position) && new_position.x != 0 && new_position.y != 0 && new_position.x != 1 && new_position.y != 1) {
            valid_position = true;
            } 
        }
        Item* new_item = (Item*) malloc(sizeof(Item));
        // while (count != FRUITS_NUM) {
        //     for (int i = 0; i <= FRUITS_NUM; i++) {
        //         new_item->type = FRUIT;
        //         new_item->position = new_position;
        //         new_item->draw = NULL;
        //         new_item->data = NULL;
        //         LLNode* node = create_llnode(new_item);
        //         insertTail(items->items_list, node);
        //         count++;
        //     }
        //     continue;
        // }
        // printf("%d", rand() % 3);
        int type = rand() % 5;
        while(type == FRUIT){
            type = rand() % 5;
        }
        // rand() % 6
        new_item->type = type;
        new_item->position = new_position;
        new_item->draw = NULL;
        new_item->data = NULL;
        LLNode* node = create_llnode(new_item);
        insertTail(items->items_list, new_item);
    }
    bool valid_position = false;
    point new_position;
    while(!valid_position) {
        new_position.x = rand() % 15;
        new_position.y = rand() % 15;
        if(!position_occupied(new_position) && !snake_position_occupied(new_position)) {
        valid_position = true;
        } 
    }
    Item* new_item = (Item*) malloc(sizeof(Item));
    new_item->type = DEATH_FRUIT;
    new_item->position = new_position;
    new_item->draw = NULL;
    new_item->data = NULL;
    LLNode* node = create_llnode(new_item);
    insertTail(items->items_list, new_item);
}


// 2035TODO
// This function should check if the snake's head collides with any items and handle each possible collision accordingly
// Should return 1 for a GAME-ENDING collision, 0 otherwise
bool check_item_collision() {
    // If an item is eaten, it should be replaced at a new location
    Snake* snake = get_snake();
    LLNode* curr = items->items_list->head;
    LLNode* current = snake->snake_list->head;
    SnakeItem* snake_pos = (SnakeItem*) current->data;
    while(curr != NULL) {
        Item* item = (Item*) curr->data;
        if(item->position.x == snake_pos->position.x && item->position.y == snake_pos->position.y) {
            switch(item->type) {
                case FRUIT:
                    if(snake->boosted != 0){
                        printf("You hit a fruit\n");
                        grow_snake();
                        grow_snake();
                    } else{
                        printf("You hit a fruit\n");
                        grow_snake();
                    }
                    break;
                case BOOST:
                    printf("You hit a boost\n");
                    snake->boosted = 10;
                    break;
                case POISON:
                    printf("You hit a poison\n");
                    if(snake->boosted != 0){
                        snake->score -= 2;
                    } else{
                        printf("You hit a poison\n");
                        if (snake->score > 0){
                        snake->score--;
                        }
                    }
                    break;
                case FAST_FRUIT:
                    printf("you ate a speed fruit");
                    snake->speed = 5;
                    break;
                case CLOUD_FRUIT:
                printf("you ate a CLOUD fruit");
                    snake->cloud_active = true;
                    snake->cloud_timer = 10;
                    break;
                case DEATH_FRUIT:
                    printf("you ate a death fruit");
                    snake->death_collision = true;
                    break;
            }
            replace_item(curr);
            return 0;
        }
        curr = curr->next;
    }

    return 0;
}

// 2035TODO
// This function should delete and replace an item that was eaten by the snake
void replace_item(LLNode* current_item) {
    srand(time(0));
    Item* item = (Item*) current_item->data;
    int type = item->type;
    delete item;
    bool valid_position = false;
    point new_position;
    while(!valid_position){
        new_position.x = rand() % 15;
        new_position.y = rand() % 15;
        if (!position_occupied(new_position) && !snake_position_occupied(new_position) && new_position.x != 0 && new_position.y != 0 && new_position.x != 1 && new_position.y != 1){
            valid_position = true;
        }
    }
    Item* new_item =(Item*) malloc(sizeof(Item));
    new_item->type = type;
    new_item->position = new_position;
    new_item->data = NULL;
    current_item->data = new_item;
}

//2035TODO
// This function should draw all of the items in the Items linked list
// This should be VERY similar to the draw_snake() function
void draw_items(void) {
    LLNode* curr = items->items_list->head;
    while(curr != NULL) {
        Item* item = (Item*) curr->data;
        if(item->draw == NULL) {
            switch(item->type) {
                case FRUIT:
                    draw_fruit(item->position.x, item->position.y);
                    break;
                case BOOST:
                    draw_boost(item->position.x, item->position.y);
                    break;
                case POISON:
                    draw_poison(item->position.x, item->position.y);
                    break;
                case FAST_FRUIT:
                    draw_fast(item->position.x, item->position.y);
                    break;
                case CLOUD_FRUIT:
                    draw_cloud(item->position.x, item->position.y);
                    break;
                case DEATH_FRUIT:
                    draw_death(item->position.x, item->position.y);
                    break;
            }
        }
        curr = curr-> next;
    }
}

Items* get_items(void) {
    return items;
}


void reshuffle_items() {
    // Items* current_items = get_items();
    // point valid_positions[256];
    // int valid_count = 0;

    // // 1. Pre-generate all valid positions
    // for(int x=0; x<16; x++) {
    //     for(int y=0; y<16; y++) {
    //         point p = {x, y};
    //         if(!snake_position_occupied(p)) {
    //             valid_positions[valid_count++] = p;
    //         }
    //     }
    // }

    // // 2. Fisher-Yates shuffle
    // for(int i=valid_count-1; i>0; i--) {
    //     int j = rand() % (i+1);
    //     point temp = valid_positions[i];
    //     valid_positions[i] = valid_positions[j];
    //     valid_positions[j] = temp;
    // }

    // // 3. Assign new positions
    // LLNode* curr = current_items->items_list->head;
    // for(int i=0; curr && i<valid_count; i++) {
    //     ((Item*)curr->data)->position = valid_positions[i];
    //     curr = curr->next;
    // }

    // draw_items();



    Items* current_items = get_items();
    LLNode* curr = (LLNode*) items->items_list->head;
    while(curr) {
        switch(get_snake()->map){
            case 1:
                replace_jungle_map(((Item*)curr->data)->position.x, ((Item*)curr->data)->position.y);
                break;
            case 2:
                replace_ocean_map(((Item*)curr->data)->position.x, ((Item*)curr->data)->position.y);
                break;
        }
        curr = curr->next;
    }

    curr = (LLNode*) items->items_list->head;
    while(curr){
        bool valid_position = false;
        point new_pos;

        // Find non-colliding position
        while(!valid_position) {
            new_pos.x = rand() % 16;
            new_pos.y = rand() % 16;
            
            if(!position_occupied(new_pos) && !snake_position_occupied(new_pos)) {
                valid_position = true;
            }
        }
        // new_pos = {4, 2};
        ((Item*)curr->data)-> position = new_pos;
        curr = curr->next;
    }
    //curr = (LLNode*) current_items->items_list->head;

    draw_items();

    
    // Clear existing items
    // destroyList(current_items->items_list);
    // current_items->items_list = create_dlinkedlist();

    // // Regenerate 5 fruits + 10 random items
    // for(int i=0; i<14; i++) {
    //     bool valid_position = false;
    //     point new_pos;

    //     // Find non-colliding position
    //     while(!valid_position) {
    //         new_pos.x = rand() % 16;
    //         new_pos.y = rand() % 16;
            
    //         if(!position_occupied(new_pos) && !snake_position_occupied(new_pos)) {
    //             valid_position = true;
    //         }
    //     }

    //     // Create item
    //     Item* new_item = new Item();
    //     if(i < FRUITS_NUM) { // First 5 are always fruits
    //         new_item->type = FRUIT;
    //         new_item->draw = draw_fruit;
    //     } else { // Last 9 are random
    //         new_item->type = rand() % 5;
    //         switch(new_item->type) {
    //             case FRUIT: new_item->draw = draw_fruit; break;
    //             case BOOST: new_item->draw = draw_boost; break;
    //             case POISON: new_item->draw = draw_poison; break;
    //             case FAST_FRUIT: new_item->draw = draw_fast; break;
    //             case CLOUD_FRUIT: new_item->draw = draw_cloud; break;
    //         }
    //     }
    //     new_item->position = new_pos;

    //     // Add to list
    //     insertTail(current_items->items_list, create_llnode(new_item));
    // }
    // bool valid_position = false;
    // point new_pos;

    // // Find non-colliding position
    // while(!valid_position) {
    //     new_pos.x = rand() % 16;
    //     new_pos.y = rand() % 16;
            
    //     if(!position_occupied(new_pos) && !snake_position_occupied(new_pos)) {
    //         valid_position = true;
    //     }
    // }
    // Item* new_item = new Item();
    // new_item->type = DEATH_FRUIT;
    // new_item->draw = draw_death;
    // new_item->position = new_pos;
    // insertTail(current_items->items_list, create_llnode(new_item));
}


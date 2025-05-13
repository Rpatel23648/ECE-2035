// ============================================
// The Snake class file
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "snake.h"
#include "doubly_linked_list.h"
#include "hardware.h"
#include <string>
#include <typeinfo>
#include "graphics.h"

Snake* snake;
DLinkedList* SnakeDLL = NULL;

// 2035TODO
// This function should initialize the Snake struct and populate its linked list with 10 SnakeItems.
void snake_init()
{
    //srand(time(0));
    snake = (Snake*)malloc(sizeof(Snake));
    snake->snake_list = create_dlinkedlist();
    snake->score = 0;
    snake->direction = RIGHT;
    snake->length = 6;
    snake->boosted = 0;
    snake->speed = 0;
    snake->cloud_active = false;
    snake->cloud_timer = 0;
    snake->lives = 3;
    snake->death_collision = false;
    snake->easy_mode = NULL;
    point init_location = {8,8};
    // Take a look at snake.h to see how the Snake and SnakeItem structs work!
    for (int i = 0; i < snake->length; i++) {
        SnakeItem* new_segment = (SnakeItem*)malloc(sizeof(SnakeItem));
        new_segment->position = init_location;

        if (i == 0) {
            new_segment->draw = draw_snake_head;
        }
        else {
            new_segment->draw = draw_snake_body;
        }

        // printf("Assigned %p to new segment %d\n", new_segment->draw, i);
        // printf("Pos: %d, %d\n", new_segment->position.x, new_segment->position.y);

        new_segment->data = NULL;
        LLNode* node = create_llnode(new_segment);

        SnakeItem* data = (SnakeItem*) node->data;
        // printf("draw: %p\n", data->draw);

        insertTail(snake->snake_list, new_segment);
        init_location.x--;
    }
    init_location.x++;
    snake->previous_tail_position = init_location;
}

// 2035TODO
// This function updates the location of the SnakeItems in the Snake's DLL
void move_snake() {
    printf("move snake\n");
    // Hint: you'll want to use previous_tail_position for this function
    Snake* snake = get_snake();
    LLNode* head_node = snake->snake_list->head;
    point new_head_position = ((SnakeItem*)head_node->data)->position;
    
    switch(snake->direction){
        case RIGHT:
            new_head_position.x++;
            if (snake->easy_mode){
                if (new_head_position.x >= SIZE_X/CELL_SIZE ) {
                    new_head_position.x = new_head_position.x % (SIZE_X/CELL_SIZE);
                }
            }
            break;
        case LEFT:
            new_head_position.x--;
            if (snake->easy_mode){
                if (new_head_position.x <= 0) {
                    new_head_position.x = new_head_position.x + SIZE_X/CELL_SIZE; 
                }
            }
            break;
        case UPWARD:
            new_head_position.y++;
            if (snake->easy_mode){
                if (new_head_position.y >= SIZE_Y/CELL_SIZE) {
                    new_head_position.y = new_head_position.y % (SIZE_Y/CELL_SIZE) + 1;
                }
            }
            break;
        case DOWNWARD:
            new_head_position.y--;
            if (snake->easy_mode){
                if (new_head_position.y <= 1) {
                    new_head_position.y = SIZE_Y/CELL_SIZE  ;
                }
            }
            break;
    }
    LLNode* tail_node = getTail(snake->snake_list);
    while(tail_node->prev != NULL) {
        ((SnakeItem*)tail_node->data)->position = ((SnakeItem*)tail_node->prev->data)->position;
        tail_node = tail_node->prev;
    }
    ((SnakeItem*)head_node->data)->position = new_head_position;
    switch (snake->map){
        case 1:
            replace_jungle_map(snake->previous_tail_position.x, snake->previous_tail_position.y);
            break;
        case 2:
            replace_ocean_map(snake->previous_tail_position.x, snake->previous_tail_position.y);
            break;
        default:
            draw_nothing(snake->previous_tail_position.x, snake->previous_tail_position.y);
            break;
    }
    snake->previous_tail_position = ((SnakeItem*)snake->snake_list->tail->data)->position;
    if (snake->boosted != 0) {
        snake->boosted--;
    }
    if (snake->speed != 0 ) {
        snake->speed--;
    }
    if (snake->cloud_timer != 0) {
        snake->cloud_timer--;
    }
    if (snake->cloud_timer == 0) {
        snake->cloud_active = false;
    }
    
// //DEBUG : START
//     LLNode* curr = (LLNode*) snake->snake_list->head;
//     while(curr != NULL) {
//         printf("\npos: %d, %d\n", ((SnakeItem*)curr->data)->position.x, ((SnakeItem*)curr->data)->position.y);
//         curr = curr->next;
//     }
// //DEBUG : END

    // if (getSize(snake->snake_list) > snake->length) {
    //     LLNode* tail_node = snake->snake_list->tail;
    //     snake->previous_tail_position = ((SnakeItem*)tail_node->data)->position;
    //     printf("Deleting backend\n");
    //     deleteNode(snake->snake_list, tail_node);
    // }
}

// 2035TODO
// This function should check if the Snake has collided with a wall, returns 1 on collision
// Note that the left and top of the uLCD are x=0 and y=0, respectively
// The right and bottom of the screen are SIZE_X/CELL_SIZE and SIZE_Y/CELL_SIZE, respectively
bool check_wall_collision() {
    LLNode* head_node = snake->snake_list->head;
    SnakeItem* head = (SnakeItem*) head_node->data;
    if (head->position.x <= 0 || head->position.x >= SIZE_X/CELL_SIZE || head->position.y <= 0 || head->position.y >= SIZE_Y/CELL_SIZE) {
        printf("you hit a wall\n");
        return 1;
    }
    return 0;
}


// 2035TODO
// This function should check if the Snake has collided with itself, returns 1 on collision
bool check_self_collision() {
    LLNode* head_node = snake->snake_list->head;
    SnakeItem* head = (SnakeItem*) head_node->data;
    LLNode* curr = head_node->next;
    while(curr != NULL) {
        SnakeItem* item = (SnakeItem*) curr->data;
        if (head->position.x == item->position.x && head->position.y == item->position.y){
            printf("you hit yourself");
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

// 2035TODO
// This function should increase the physical length of the Snake.
void grow_snake() {
    SnakeItem* new_tail = (SnakeItem*) malloc(sizeof(SnakeItem));
    new_tail->position = snake->previous_tail_position;
    new_tail->draw = draw_snake_body;
    new_tail->data = NULL;
    LLNode* node = create_llnode(new_tail);
    insertTail(snake->snake_list, node);
    snake->length++;
    snake->score++;
}

// 2035TODO
// This function should draw all the SnakeItems in the Snake linked list
void draw_snake(void) {
    LLNode* curr = snake->snake_list->head;
    while(curr != NULL) {
        SnakeItem* item = (SnakeItem*) curr->data;
        if (item->draw){
            item->draw(item->position.x, item->position.y);
        }

    curr = curr->next;
    }
}

Snake* get_snake(void) {
    return snake;
}

point get_snake_head_location(void) {

    LLNode* head = SnakeDLL->head;
    return ((SnakeItem*)head->data)->position;
}

void reverse_snake() {
    Snake* snake = get_snake();
    switch(snake->direction) {
        case RIGHT:
            snake->direction = LEFT;
            break;
        case LEFT:
            snake->direction = RIGHT;
            break;
        case UPWARD:
            snake->direction = DOWNWARD;
            break;
        case DOWNWARD:
            snake->direction = UPWARD;
            break;
        default:
            break;
    }
    DLinkedList* list = snake->snake_list;
    LLNode* newHead = getTail(list);
    LLNode* newTail = getHead(list);
    list->head = newHead;
    list->tail = newTail;
    LLNode* curr = newHead;
    LLNode* prev = NULL;

    while(curr) {
        LLNode* next = curr->prev; 
        curr->prev = prev;
        curr->next = next;
        
        prev = curr;
        curr = next;
    }
    SnakeItem* headItem = (SnakeItem*)getData(newHead);
    headItem->draw = draw_snake_head;
    SnakeItem* tailItem = (SnakeItem*)getData(newTail);
    tailItem->draw = draw_snake_body;
    snake->previous_tail_position = tailItem->position;
}


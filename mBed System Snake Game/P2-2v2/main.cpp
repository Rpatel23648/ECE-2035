//=================================================================
// The main program file.
//
// Copyright 2025 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <cstdio>
#include <stdlib.h>

// Project Includes
#include "globals.h"
#include "hardware.h"
#include "mbed_retarget.h"
#include "snake.h"
#include "items.h"
#include "doubly_linked_list.h"
#include "graphics.h"
#include "LittleFileSystem.h"
#include "mbed.h"
#include "FlashIAP.h"

#define TICK_RATE 2
#define WIN_SCORE 10

FlashIAP flash;

void save_highscore(int score) {
    flash.init();
    
    uint32_t base = flash.get_flash_start();
    uint32_t size = flash.get_flash_size();
    uint32_t sector_size = flash.get_sector_size(base + size - 1);
    uint32_t addr = base + size - sector_size;

    if(flash.erase(addr, sector_size) == 0) {
        flash.program(&score, addr, sizeof(score));
    }

    flash.deinit();
}

int load_highscore() {
    flash.init();
    
    uint32_t base = flash.get_flash_start();
    uint32_t size = flash.get_flash_size();
    uint32_t addr = base + size - flash.get_sector_size(base + size - 1);

    int score = 0;
    flash.read(&score, addr, sizeof(score));
    
    flash.deinit();
    return score;
}


//1 - Baby
//2 - Normal
//3 - Insane
// LittleFileSystem fs("fs");

int main()
{

    printf("Initialization starting\n");
    GameInputs inputs;
    ASSERT_P(hardware_init() == ERROR_NONE, -1);
    
    Timer t;
    t.start();
    int game_mode;
    int win_score;
    int tick_rate;
    bool wrap_around;
    int highscore;
    int map;
    bool shuffle;
    // FILE *file = fopen("/fs/highscore.txt", "r");
    // if (file == NULL) {
    //     perror("Error opening file");
    //     highscore = 0;
    // } else{
    //     fscanf(file, "%d", &highscore);
    // }
    highscore = load_highscore();

    // This is the text that prints on the start screen
    while(1) {
        inputs = read_inputs();
        uLCD.locate(0, 0);
        uLCD.printf("Select your diff\n (Highscore: %d).\n", highscore);
        uLCD.locate(0,3);
        uLCD.printf("Baby - Button 1\nNormal- Button 2\nInsane- Button 3\n");

        if(inputs.b1) {
            game_mode = 1;
            printf("\nthis is button 1, u got baby.\n");
            break;
        } 
        if(inputs.b2) {
            game_mode = 2;
            printf("\nthis is button 2, u got normal.\n");
            break;
        }
        if(inputs.b3) {
            game_mode = 3;
            printf("\nthis is button 3, u got insane.\n");
            break;
        }  
    }

    uLCD.cls();

    while(1) {
        inputs = read_inputs();
        uLCD.printf("Choose your map:\n");
        uLCD.locate(0,3);
        uLCD.printf("Normal - Button 1\nJungle - Button 2\nOcean - Button 3\n");

        if(inputs.b1) {
            printf("\nthis is button 1, u got normal.\n");
            uLCD.cls();
            srand(t.elapsed_time().count());
            break;
        } 
        if(inputs.b2) {
            printf("\nthis is button 2, u got jungle.\n");
            uLCD.cls();
            draw_jungle_map();
            map = 1;
            srand(t.elapsed_time().count());
            break;
        }
        if(inputs.b3) {
            printf("\nthis is button 3, u got ocean.\n");
            uLCD.cls();
            draw_ocean_map();
            map = 2;
            srand(t.elapsed_time().count());
            break;
        }
    }
    

    // This loop is for the start screen
    // While the user has not provided an input, the game should remain on the start screen
    
    
    
    // while(1){
    //     // 2035TODO
    //     // you need to implement read_inputs to get past the start screen!!
    //     inputs = read_inputs();
    //     if (inputs.up || inputs.down || inputs.right || inputs.left || inputs.center || inputs.b1 || inputs.b2 || inputs.b3) {
    //         printf("you hit a button\n");
    //         srand(t.elapsed_time().count()); // this line sets the random seed
    //         break;
    //     }
    // }

    
    
    

    // 2035TODO
    // initialize the Snake and the Items
    snake_init();
    if(game_mode == 1){
        get_snake()->easy_mode = true;
    }
    get_snake()->map = map;
    items_init();
    
    bool game_over = false;
    bool game_won = false;
    uLCD.baudrate(115200);

    switch(game_mode){
        case 1:
            get_snake()->lives = 5;
            wrap_around = true;
            win_score = 10;
            tick_rate = 4;
            shuffle = false;
            break;
        case 2:
            get_snake()->lives = 3;
            wrap_around = false;
            win_score = 25;
            tick_rate = 3;
            shuffle = false;
            break;
        case 3:
            get_snake()->lives = 1;
            wrap_around = false;
            win_score = 2500;
            tick_rate = 1;
            shuffle = true;
            get_snake()->shuffle = true;
            break;
    }
    int tick = 0;
    // 2035TODO
    // Implement the main game loop
    
    
    
    
    while(1)
    {

        wait_us(40000); // Recovery time

        // 1. draw the items and the snake
        draw_snake();
        draw_items();
        // 2. print the score and the snake's 'boosted' value at the top of the screen
            // check out uLCD.locate() and uLCD.printf()
        uLCD.locate(0,0); 
        uLCD.printf("S:%d B:%d Sp: %d L: %d", get_snake()->score, get_snake()->boosted, get_snake()->speed, get_snake()->lives);

        // 3. check for collision -> if a GAME-ENDING collision occurs, end the game with a game over screen
            // self collision
            // item collision
            // wall colliison

            //this now works for when cloud cloud fruit is active.
        if (get_snake()->cloud_active){
            if(check_wall_collision()) {
                if(get_snake()->lives != 1){
                    if (game_mode != 1){
                        get_snake()->lives--;
                    }
                } else{
                    printf("you hit a wall");
                    game_over = true;
                }
            } else {
                if(check_item_collision()){ //Advance Feature Moving sprites
                    if(get_snake()->shuffle){
                        printf("\nshuffle items\n");
                        reshuffle_items();
                    }
                }
            }
        } else {
                if(check_self_collision() || check_wall_collision()) {
                    if(get_snake()->lives != 1){
                        if (game_mode != 1){
                            get_snake()->lives--;
                        }
                    } else{
                        printf("you hit a wall or urself\n");
                        game_over = true;
                    }
                }
                else {
                    if(check_item_collision()){ //Advance Feature Moving sprites
                        if(get_snake()->shuffle){
                            printf("\nshuffle items\n");
                            reshuffle_items();
                }
            }
        }
    }
            
        if (get_snake()->death_collision){
            if(game_mode == 1){
                if(get_snake()->lives != 1){
                    get_snake()->lives--;
                    get_snake()->death_collision = false;
                } else{
                    printf("you hit a death fruit");
                    game_over = true;
                }
            } else{
                printf("you hit a death fruit");
                game_over = true;
            }
        }    
        // if(check_self_collision() || check_wall_collision()) {
        //     game_over = true;
        // }
        // else {
        //     check_item_collision();
        // }

        // 4. check if the snake's score >= 10 -> if so end the game with a game win screen
            // for 3 and 4, check out uLCD.cls()
        if (get_snake() ->score >= win_score) {
            game_won = true;
        }
        if (game_over || game_won) {
            uLCD.cls();
            uLCD.locate(3, 5);
            if(game_over) {
            uLCD.printf("GAME OVER!");
            } else {
                uLCD.printf("YOU WIN!\n SCORE: %d", get_snake()->score);
             }
            break;
        }
        // // 5. read the user inputs and update the snake direction if necessary
        inputs = read_inputs();
        if(inputs.right && get_snake()->direction != LEFT) {
            get_snake()->direction = RIGHT;
        } else if (inputs.left && get_snake()->direction != RIGHT) {
            get_snake()->direction = LEFT;
        } else if (inputs.up && get_snake()->direction != DOWNWARD) {
            get_snake()->direction = UPWARD;
        } else if (inputs.down && get_snake()->direction != UPWARD) {
            get_snake()->direction = DOWNWARD;
        } else if (inputs.center) {
            reverse_snake(); // Advance Feature
        }

        // // 6. move the snake (you might not want the snake to move every loop)
        if (tick % tick_rate == 0) {
            if (get_snake() -> speed != 0){
                if(get_snake()->cloud_active){
                    draw_snake();
                }
                if(game_mode == 3){
                    move_snake();
                    reshuffle_items();
                    move_snake();
                    reshuffle_items();
                } else {
                    move_snake();
                    move_snake();
                }
            } else {
                if(game_mode == 3){
                    move_snake();
                    reshuffle_items();
                } else {
                    move_snake();
                }
            }
        }
        tick++;
        t.reset();
    }

    printf("out of main loop\n");
    
    //should save highscore
    // if (get_snake()->score > highscore){
    //    file = fopen("/fs/highscore.txt", "w");
    //     if (file == NULL) {
    //         perror("Error opening file");
    //         return 1;
    //     } else{
    //         fprintf(file, "%d", &highscore);
    //     } 
    // }
    if(get_snake()->score > highscore) {
        save_highscore(get_snake()->score);
    }
    
    
    
    destroyList(get_snake()->snake_list);
    destroyList(get_items()->items_list);
    free(get_snake());
    free(get_items());

    return 0;
}
// ============================================
// The header file for the hardware components
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#ifndef HARDWARE_H
#define HARDWARE_H

// Structure that represents all the inputs to the game.
// If additional hardware is added, new elements should be added to this struct.
struct GameInputs {
    int up, down, left, right, center;     // Button presses
    int b1, b2, b3;
};

int hardware_init();

GameInputs read_inputs();

void print(const char* c);
#endif // HARDWARE_H
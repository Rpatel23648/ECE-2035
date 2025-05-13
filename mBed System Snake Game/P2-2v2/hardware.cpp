// ============================================
// The file for all of the Mbed's hardware peripherals
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "globals.h"

#include "hardware.h"

// Hardware initialization: Instantiate all the things!
uLCD_4DGL uLCD(p9,p10,p11); // LCD Screen (tx, rx, reset)
Nav_Switch myNav(p12, p15, p14, p16, p13); // initialize nav switch
BufferedSerial pc(USBTX, USBRX, 115200);  // USB Console (tx, rx)
DigitalIn button1(p21);  // Pushbuttons (pin)
DigitalIn button2(p22);
DigitalIn button3(p23);

AnalogOut DACout(p18); // Speaker (pin)
PwmOut speaker(p25); 

int hardware_init()
{    
    button1.mode(PullUp); 
    button2.mode(PullUp);
    button3.mode(PullUp);
    return ERROR_NONE;
}

// 2035TODO
// This function reads the inputs (nav switch, buttons) and stores their values in the GameInputs struct
// The current code is placeholder, replace it!
// HINT: lookup your NavSwitch under mbed site > Hardware> Components and look at demo code
GameInputs read_inputs() 
{
    GameInputs in;
    
    // 1. read and invert the buttons (the buttons are active-low)
    in.b1 = !button1.read();
    in.b2 = !button2.read();
    in.b3 = !button3.read();

    // 2. read the navswitch
    in.up= myNav.down();
    in.down=myNav.up();
    in.left= myNav.left();
    in.right = myNav.right();
    in.center = myNav.center();

    return in;
}


// A shortcut to serial port print
void print(const char* c)
{
    pc.write(c, strlen(c));
}
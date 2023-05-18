/***************************************************************************************************
 * Terminarium - Keyboard & user input functions
 * File: {@code user_input.h} [header file]
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#ifndef USER_INPUT_H
#define USER_INPUT_H                           // header guard

#include "screen_control.h"                    // import screen controlling functions
extern Screen screen;                          // include global screen state variable in current scope  

#include "mqtt.h"                              // import mqtt connectivity functions
extern char* SSID;                             // include wifi network name
extern char* PASSWORD;                         // include wifi network password
extern char* SERVER;                           // include mqtt broker address

#define KEY_ROWS 4                             // number of rows of the keyboard
#define KEY_COLUMNS 23                         // number of columns of the keyboard
#define KEY_X 12                               // x position of leftmost column
#define KEY_Y 130                              // y position of topmost row

// multidimensional array containing the available characters on the keyboard
extern const char keyboard[4][23];

// character arrays that stores the user inputted Strings
extern char inputSSID[32];                     // stores the user inputted Wifi SSID
extern char inputPSWD[32];                     // that stores the user inputted Wifi password
extern char inputMQTT[32];                     // stores the user inputted mqtt broker address     

// variables indicating currently highlighted character
extern int currentXY[2];                       // x, y coords of highlighted character 
extern int currentChar[2];                     // index values to retrieve highlighted character from keyboard array

// function called on right button press in user input screen
extern void keyboardRight();

// function called on left button press in user input screen
extern void keyboardLeft();

// function called on up button press in user input screen
extern void keyboardUp();

// function called on down button press in user input screen
extern void keyboardDown();

// function called on middle button press in user input screen
extern void keyboardMiddle();

// function to add currently highlighted character to input String array
extern void addChar(char character);

// function to remove last character from the input String array
extern void removeChar();

// function to import provided network credential and reset the position of highlighted key
extern void initUserInput(char* currentVal);

// function to save user input upon selecting the ENTER key
extern void saveUserInput();

#endif
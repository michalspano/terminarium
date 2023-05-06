/***************************************************************************************************
 * Terminarium - LCD screen drawing functions
 * File: {@code screen_draw.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#ifndef SCREEN_DRAW_H
#define SCREEN_DRAW_H                              // header guard

#include "TFT_eSPI.h"                              // import TFT LCD library 
extern TFT_eSPI tft;                               // include wio terminal LCD screen variable in current scope 

#include "screen_control.h"                        // include screen control functions
extern Screen screen;                              // include global screen state variable in current scope
extern Screen oldScreen;                           // include global oldScreen state variable in current scope

#include "utils.h"                                 // include utility functions

#define HEIGHT 240                                 // define LCD screen pixel height
#define WIDTH 320                                  // define LCD screen pixel width
#define CHAR_HEIGHT 24                             // define pixel height of one character
#define CHAR_WIDTH 18                              // define pixel width of one character


// *************************** MISC ********************************** //

// function that clears screen for switching screen states
extern void clearScreen();

// function that calculates centered x position for any given text
extern int getCenterX(char* text);

/* @drawTriangles - draw triangle graphics (common in all sensor screens)
 * used to visually communicate that screens can be cycled through using left/right button inputs <..> */
extern void drawTriangles();


// ************************** HEADER ********************************* //

// draw header & background for all screens
extern void drawHeader();

// draw icon in header indicating connectivity status 
extern void drawConnStatus(bool mqttConnected);


// ************************* DASHBOARD ******************************* //

// draw dashboard element (sensor panels)
extern void drawDashboardElem(Screen type, String heading, int headingX, int headingY, int max, int min, int value, int valueX, int valueY, String unit, int unitX, int unitY);

// draw dashboard (main screen)
extern void drawDashboardScreen(int temp, int oldTemp, int humi, int oldHumi, int vib, int oldVib, int moist, int oldMoist, int light, int oldLight, int loud, int oldLoud);


// ************************ SENSOR SCREENS *************************** //

// draw status data (common for all individual sensor screens)
extern void drawStatus(int value, int max, int min);

// draw individual sensor screens, which can be cycled through using button inputs
extern void drawSensorScreen(Screen type, String heading, int headingX, int headingY, int max, int min, int value, int valueX, int valueY, String unit, int unitX, int unitY);


// ******************** CONNECTIVITY SCREENS ************************* //

extern void drawUpdateScreen();

extern void drawConnSelectScreen(bool isStartup);

extern void drawConnectScreen(char* connectType, const char* connectValue); 

extern void drawConnectedText();


// **************************** GENERAL ****************************** //

// general function that draws all screens, called directly from main program loop
extern void drawScreen(int temp, int humi, int vib, int moist, int light, int loud, bool isStartup, bool mqttConnected);

#endif
/***************************************************************************************************
 * Terminarium - LCD screen drawing functions
 * File: {@code screen_draw.h} [header file]
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#ifndef SCREEN_DRAW_H
#define SCREEN_DRAW_H                              // header guard

#include "TFT_eSPI.h"                              // import TFT LCD library 
extern TFT_eSPI tft;                               // include wio terminal LCD screen variable in current scope 

#include "screen_control.h"                        // import screen control functions
extern Screen screen;                              // include global screen state variable in current scope
extern Screen oldScreen;                           // include global oldScreen state variable in current scope
extern boolean buttonPressed;                      // boolean indicating button press, used to determine when to redraw screen user-input screen  

#include "mqtt.h"                                  // import mqtt connectivity functions
extern char* SSID;                                 // include wifi network name
extern char* SERVER;                               // include mqtt broker address
extern bool wifiWasConnected;                      // include flag indicating user was previously connected to wifi server
extern bool mqttWasConnected;                      // include flag indicating user was previously connected to mqtt server

#include "user_input.h"                            // import user input functions
extern char inputSSID[32];                         // include character array that stores the user inputted Wifi SSID
extern char inputPSWD[32];                         // include character array that that stores the user inputted Wifi password
extern char inputMQTT[32];                         // include character array that stores the user inputted mqtt broker address    

#include "utils.h"                                 // import utility functions

#define TFT_HEIGHT 240                             // define LCD screen pixel height
#define TFT_WIDTH 320                              // define LCD screen pixel width
#define CHAR_HEIGHT_2 14                           // define pixel height of one character (size 2)
#define CHAR_WIDTH_2 12                            // define pixel width of one character (size 2)
#define CHAR_HEIGHT_3 24                           // define pixel height of one character (size 3)
#define CHAR_WIDTH_3 18                            // define pixel width of one character (size 3)


// **************************** GENERAL ****************************** //

// general function that draws all screens, called directly from main program loop
extern void drawScreen(int temp, int humi, int vib, int moist, int light, int loud, bool isStartup);


// ************************** HEADER ********************************* //

// draw header & background for all screens
extern void drawHeader();

// draw icon in header indicating connectivity status 
void drawConnStatus(bool connected, char* text1, char* text2, int x, int y);


// ************************* DASHBOARD ******************************* //

// draw dashboard (main screen)
extern void drawDashboardScreen(int temp, int oldTemp, int humi, int oldHumi, int vib, int oldVib, int moist, int oldMoist, int light, int oldLight, int loud, int oldLoud);

// draw dashboard element (sensor panels)
extern void drawDashboardElem(Screen type, String heading, int headingX, int headingY, int min, int max, int value, int valueX, int valueY, String unit, int unitX, int unitY);


// ************************ SENSOR SCREENS *************************** //

// draw individual sensor screens, which can be cycled through using button inputs
extern void drawSensorScreen(Screen type, String heading, int headingX, int headingY, int min, int max, int value, int valueX, int valueY, String unit, int unitX, int unitY);

// draw status data (common for all individual sensor screens)
extern void drawStatus(int value, int min, int max);


// ********************* USER INPUT SCREENS ************************** //

// function to draw user input screen and its components
extern void drawInputScreen(char* userInput);

// function to draw keyboard
extern void drawKeyboard();

// function to draw character currently highlighted on keyboard
extern void drawSelection();

// draw user inputted String as it being typed
extern void drawUserInput(char* userInput);


// ******************** CONNECTIVITY SCREENS ************************* //

// draw update screen indicating new sensor ranges are received
extern void drawUpdateScreen();

// draw screen that prompts user with choice to connect or not
extern void drawConnSelectScreen(bool isStartup);

// draw screen to confirm that network info is correct
void drawConnConfirmScreen();

// draw wifi or mqtt connection screen depending on screen context
extern void drawConnectScreen(char* connectType, const char* connectValue); 

// draw green "Connected" text upon establishing conneciton (wifi and mqtt)
extern void drawConnectedText();


// *************************** MISC ********************************** //

// function that clears screen for switching screen states
extern void clearScreen();

// function that calculates centered x starting position for any given text
extern int getCenterX(char* text, int textSize);

// draw triangle graphics (common in all sensor screens)
extern void drawTriangles();

// draw dot dot dot writing effect when establishing connectivity
extern void drawDotDotDot(int length, int x, int y);

#endif                                             // end header guard  
/***************************************************************************************************
 * Terminarium - LCD screen controller
 * File: {@code screen_control.h} [header file]
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#ifndef SCREEN_CONTROL_H
#define SCREEN_CONTROL_H            // header guard

enum Screen {                       // enums denoting screen state 
  DASHBOARD,                        // dashboard displaying all 6 sensor readings
  TEMP,                             // sensor screen displaying temperature info
  HUMI,                             // sensor screen displaying humidity info
  VIB,                              // sensor screen displaying vibration info
  MOIST,                            // sensor screen displaying moisture info
  LIGHT,                            // sensor screen displaying light info
  LOUD,                             // sensor screen displaying loudness info
  CONNECT_SELECT,                   // screen prompting user to choose if they want to establish mqtt connection
  CONNECT_CONFIRM,                  // screen allowing users to connect with current network details or choose to modify them
  USER_INPUT_SSID,                  // screen with keyboard allowing user to type new wifi network SSID
  USER_INPUT_PSWD,                  // screen with keyboard allowing user to type new wifi network password
  USER_INPUT_MQTT,                  // screen with keyboard allowing user to type new MQTT broker address
  CONNECT_WIFI,                     // screen displaying wifi network connection progress
  CONNECT_MQTT,                     // screen displaying mqtt broker connection progress
  UPDATE                            // screen notifying of new incoming sensor ranges
};

#define DEBOUNCE_LIMIT 300          // time (ms) required between button presses to register input (used to debounce unwanted repeat inputs)

extern Screen screen;               // include global screen state variable in current scope 
extern Screen oldScreen;            // include global oldScreen state variable in current scope
extern bool shouldUpdateOldScreen;  // include boolean for if oldScreen should be updated
extern bool isStartup;              // include boolean for if program is at startup

#include "mqtt.h"                   // import mqtt connectivity functions
extern char* SSID;                  // include wifi network name
extern bool wifiWasConnected;       // include flag indicating user was previously connected to wifi server
extern bool mqttWasConnected;       // include flag indicating user was previously connected to mqtt server

#include "user_input.h"             // import user input functions

extern unsigned long prevInputTime; // variable tracking the last time an input was registered (used for debouncing unwanted repeat inputs)

extern boolean buttonPressed;       // boolean indicating button press, used to determine when to redraw screen user-input screen   

extern void rightButton();          // function called when right button is pressed

extern void leftButton();           // function called when left button is pressed

extern void upButton();             // function called when up button is pressed

extern void downButton();           // function called when down button is pressed

extern void midButton();            // function called when middle button is pressed

extern void topButton();            // function to jump to dashboard from any screen state

// function used to revert screen state and correctly update the oldScreen value
extern void goPrevScreen(Screen currentScreen);

#endif                              // end header guard  
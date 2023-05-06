/***************************************************************************************************
 * Terminarium - LCD screen controller
 * File: {@code screen_control.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#ifndef SCREEN_CONTROL_H
#define SCREEN_CONTROL_H            // header guard

enum Screen {                       // enums denoting screen state 
  DASHBOARD,
  CONNECT_SELECT,
  CONNECT_WIFI,
  CONNECT_MQTT,
  UPDATE,
  TEMP,
  HUMI,
  VIB,
  MOIST,
  LIGHT,
  LOUD
};

extern Screen screen;               // include global screen state variable in current scope 
extern Screen oldScreen;            // include global oldScreen state variable in current scope
extern bool shouldUpdateOldScreen;  // include boolean for if oldScreen should be updated
extern bool isStartup;              // include boolean for if program is at startup


/* @goPrevScreen - some draw functions switch between 2 screen states within 1 interval.
 * this function is used to revert screen state and correctly update the oldScreen value */
extern void goPrevScreen(Screen currentScreen);

extern void goRightScreen();        // function to cycle screen on right button press depending on current screen state

extern void goLeftScreen();         // function to switch screen on left button press depending on current screen state

extern void goDashScreen();         // function to jump to dashboard from any screen state

extern void goConnSelectScreen();   // function to jump to connection screen

#endif
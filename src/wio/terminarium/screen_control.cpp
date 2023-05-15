/***************************************************************************************************
 * Terminarium - LCD screen controller
 * File: {@code screen_control.cpp} [source file]
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#include "screen_control.h"         // include corresponding header file

static unsigned long prevInputTime = 0;

void rightButton() {                // function to cycle screen on right button press depending on current screen state
  unsigned long inputTime = millis();
  if(inputTime - prevInputTime > 200) {
    switch(screen) {
      case TEMP:
        screen = HUMI;
        break;
      case HUMI:
        screen = VIB;
        break;
      case VIB:
        screen = MOIST;
        break; 
      case MOIST:
        screen = LIGHT;
        break;
      case LIGHT:
        screen = LOUD;
        break;
      case LOUD:
        screen = DASHBOARD;
        break;
      case DASHBOARD:
        screen = TEMP;
        break;
      case CONNECT_SELECT:            // right button press = choose to connect mqtt           
        screen = CONNECT_CONFIRM;       
        isStartup = false;            // after first connect select screen it will no longer be startup
        break;
      case CONNECT_CONFIRM:
        screen = CONNECT_WIFI;
        break;
      default:                        // by default do nothing on button press                
        break;
    }
  }
  prevInputTime = inputTime;
}

void leftButton() {                 // function to switch screen on left button press depending on current screen state
  unsigned long inputTime = millis();
  if(inputTime - prevInputTime > 200) {
    switch(screen) {
      case TEMP:
        screen = DASHBOARD;
        break;
      case HUMI:
        screen = TEMP;
        break;
      case VIB:
        screen = HUMI;
        break; 
      case MOIST:
        screen = VIB;
        break;
      case LIGHT:
        screen = MOIST;
        break;
      case LOUD:
        screen = LIGHT;
        break;
      case DASHBOARD:
        screen = LOUD;
        break;
      case CONNECT_SELECT:            // left button press = choose not to connect, return to dashboard
        screen = DASHBOARD;
        isStartup = false;            // after first connect select screen it will no longer be startup 
        wifiWasConnected = false;     // opting out of connecting sets this variable to false
        mqttWasConnected = false;     // opting out of connecting sets this variable to false
        break;
      case CONNECT_CONFIRM:
        screen = CONNECT_SELECT;
        break;
      default:                        // by default do nothing on button press                
        break;
    }
  }
  prevInputTime = inputTime;
}

void upButton() {}

void downButton() {}

void midButton() {         // function to jump to connection screen
  screen = CONNECT_SELECT;
}

void topButton() {               // function to jump to dashboard from any screen state (if not currently connecting)
  if(screen != CONNECT_WIFI || screen != CONNECT_MQTT) {   
    screen = DASHBOARD;
  }
}

/**
 * @goPrevScreen: some draw functions switch between 2 screen states within 1 interval.
 * this function is used to revert screen state and correctly update the oldScreen value 
 */
void goPrevScreen(Screen currentScreen) {
  screen = oldScreen;               // set screen back to the previous screen
  oldScreen = currentScreen;        // update oldScreen value
  shouldUpdateOldScreen = false;    // ensure oldScreen update isn't overwritten in main program loop
}
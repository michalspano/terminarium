/***************************************************************************************************
 * Terminarium - LCD screen controller
 * File: {@code screen_control.cpp} [source file]
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#include "screen_control.h"           // include corresponding header file

unsigned long prevInputTime = 0;      // variable tracking the last time an input was registered (used for debouncing unwanted repeat inputs)

boolean buttonPressed = false;        // boolean indicating button press, used to determine when to redraw screen user-input screen

// function called when right button is pressed
void rightButton() {                  
  unsigned long inputTime = millis();
  if(inputTime - prevInputTime > DEBOUNCE_LIMIT) {
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
      case USER_INPUT_SSID:
        buttonPressed = true;
        keyboardRight();
        break;
      case USER_INPUT_PSWD:
        buttonPressed = true;
        keyboardRight();
        break;
      case USER_INPUT_MQTT:
        buttonPressed = true;
        keyboardRight();
        break;
      default:                        // by default do nothing on button press                
        break;
    }
  }
  prevInputTime = inputTime;
}

// function called when left button is pressed
void leftButton() {                   
  unsigned long inputTime = millis();
  if(inputTime - prevInputTime > DEBOUNCE_LIMIT) {
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
      case USER_INPUT_SSID:
        buttonPressed = true;
        keyboardLeft();
        break;
      case USER_INPUT_PSWD:
        buttonPressed = true;
        keyboardLeft();
        break;
      case USER_INPUT_MQTT:
        buttonPressed = true;
        keyboardLeft();
        break;
      default:                        // by default do nothing on button press                
        break;
    }
  }
  prevInputTime = inputTime;
}

// function called when up button is pressed
void upButton() {                     
  unsigned long inputTime = millis();
  if(inputTime - prevInputTime > DEBOUNCE_LIMIT) {
    if(screen == USER_INPUT_SSID || screen == USER_INPUT_PSWD || screen == USER_INPUT_MQTT) {
      buttonPressed = true;
      keyboardUp();
    }
  }
  prevInputTime = inputTime;
}

// function called when down button is pressed
void downButton() {
  unsigned long inputTime = millis();
  if(inputTime - prevInputTime > DEBOUNCE_LIMIT) {
    if (screen == CONNECT_CONFIRM) {
      screen = USER_INPUT_SSID;
      initUserInput(SSID);
      buttonPressed = true;
    } else if (screen == USER_INPUT_SSID || screen == USER_INPUT_PSWD || screen == USER_INPUT_MQTT) {
      keyboardDown();
      buttonPressed = true;
    }
  }
  prevInputTime = inputTime;
}

// function called when middle button is pressed
void midButton() {         
  unsigned long inputTime = millis();
  if(inputTime - prevInputTime > DEBOUNCE_LIMIT) {
    if(screen == USER_INPUT_SSID || screen == USER_INPUT_PSWD || screen == USER_INPUT_MQTT) {
      keyboardMiddle();
      buttonPressed = true;
    } else {
      screen = CONNECT_SELECT;        // by default, switch to screen for starting mqtt connection
    }
  }
}

// function to jump to dashboard from any screen state (if not currently connecting)
void topButton() {               
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
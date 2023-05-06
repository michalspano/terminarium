/***************************************************************************************************
 * Terminarium - LCD screen controller
 * File: {@code screen_control.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

enum Screen {                       // enums denoting screen state 
  DASHBOARD,
  CONNECT_GENERAL,
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
void goPrevScreen(Screen currentScreen) {
  screen = oldScreen;               // set screen back to the previous screen
  oldScreen = currentScreen;        // update oldScreen value
  shouldUpdateOldScreen = false;    // ensure oldScreen update isn't overwritten in main program loop
}

void goRightScreen() {              // function to cycle screen on right button press depending on current screen state
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
    case CONNECT_GENERAL:                       
      screen = CONNECT_WIFI;       
      isStartup = false;
      break;
    default:                        // by default do nothing on button press                
      break;
  }
}

void goLeftScreen() {               // function to switch screen on left button press depending on current screen state

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
    case CONNECT_GENERAL:
      if(isStartup) {
        screen = DASHBOARD;
      } else {
        screen = DASHBOARD;          // TODO: change to allow return to previous screen if not at startup
      }
      isStartup = false;
      break;
    default:                        // by default do nothing on button press                
      break;
  }
}

void goDashScreen() {               // function to jump to dashboard from any screen state
  screen = DASHBOARD;
}

void goConnectScreen() {            // function to jump to connection screen
  screen = CONNECT_GENERAL;
}
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
extern bool shouldUpdateOldScreen;  // include boolean if oldScreen should be updated

void goRightScreen() {              // function to cycle screen to the right depending on current screen state
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
    default:                        // default == dashboard
      screen = TEMP;
      break;
  }
}

void goLeftScreen() {               // function to cycle screen to the left depending on current screen state

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
    default:                        // default == dashboard
      screen = LOUD;
      break;
  }
}

void goDashScreen() {               // function to jump to dashboard from any screen state
  screen = DASHBOARD;
}

void goUpdateScreen() {             // function to jump to update screen when receiving new sensor ranges
  screen = UPDATE;
}

/* @goPrevScreen - some draw functions switch between 2 screen states within 1 interval.
 * this function is used to revert screen state and correctly update the oldScreen value */
void goPrevScreen(Screen currentScreen) {
  screen = oldScreen;               // set screen back to the previous screen
  oldScreen = currentScreen;        // update oldScreen value
  shouldUpdateOldScreen = false;    // ensure oldScreen update isn't overwritten in main program loop
}
/***************************************************************************************************
 * Terminarium - LCD screen controller
 * File: {@screen_control.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/
 
enum Screen {               // enums denoting screen state 
  DASHBOARD,
  TEMP,
  HUMI,
  VIB,
  MOIST,
  LIGHT,
  LOUD
};

extern Screen screen;       // include global screen state variable in current scope 

void goNextScreen() {       // function to cycle next screen depending on current screen state
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
    default:
      screen = TEMP;
      break;
  }
}

void goPrevScreen() {       // function to cycle previous screen depending on current screen state

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
    default:
      screen = LOUD;
      break;
  }
}

void goDashScreen() {       // function to jump to dashboard from any screen state
  screen = DASHBOARD;
}
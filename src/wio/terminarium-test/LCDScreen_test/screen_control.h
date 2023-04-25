enum Screen {
  DASHBOARD,
  TEMP,
  HUMI,
  VIB,
  MOIST,
  LIGHT,
  LOUD
};

extern Screen screen;

void goNextScreen() {

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

void goPrevScreen() {

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

void goDashScreen() {
  screen = DASHBOARD;
}
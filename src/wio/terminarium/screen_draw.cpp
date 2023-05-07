/***************************************************************************************************
 * Terminarium - LCD screen drawing functions
 * File: {@code screen_draw.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#include "screen_draw.h"                             // include corresponding header file

// *************************** MISC ********************************** //

// function that clears screen for switching screen states
extern void clearScreen() {
  tft.fillRect(0,50,320,TFT_HEIGHT - 50, TFT_BLACK); // clear previous screen by overwriting it with black rectangle
}


// function that calculates centered x position for any given text
int getCenterX(char* text) {
    int textSize = strlen(text) * CHAR_WIDTH;
    int xPosition = (WIDTH - textSize) / 2;
    return xPosition;
}


/* @drawTriangles - draw triangle graphics (common in all sensor screens)
 * used to visually communicate that screens can be cycled through using left/right button inputs <..> */
void drawTriangles() {                                        
  tft.fillTriangle(55, 115, 55, 135, 35, 125, TFT_WHITE);     // draw left triangle 
  tft.fillTriangle(260, 115, 260, 135, 280, 125, TFT_WHITE);  // draw right triangle 
}


void drawDotDotDot(int length, int x, int y) {
  tft.fillRect(0, y, WIDTH, CHAR_HEIGHT, TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  for(int i = 0; i < length; i++) {
    tft.drawString(".", x + (i * CHAR_WIDTH), y);
    delay(300);
  }
}


// ************************** HEADER ********************************* //

/* Note: the code for the dashboard and header has been adapted from Seeed Studio's Smart Garden project from the Wio Terminal Classroom video series:
 * Link: https://github.com/lakshanthad/Wio_Terminal_Classroom_Arduino/tree/main/Classroom%2012/Smart_Garden */

// draw header & background for all screens
void drawHeader() {
  tft.fillScreen(TFT_BLACK);                         // fill background with black color
  tft.fillRect(0,0,320,50,TFT_DARKGREEN);            // fill header rectangle with dark green 
  tft.setTextColor(TFT_WHITE);                       // set text color
  tft.setTextSize(3);                                // set text size 
  char* text = "Terminarium";
  tft.drawString(text, getCenterX(text), 14);        // draw header String
}


// draw icon in header indicating connectivity status 
void drawConnStatus(bool connected, char* text1, char* text2, int x, int y) {
  if(connected) {
    tft.fillRoundRect(x, y, 32, 32, 5, TFT_GREEN);
    tft.setTextSize(2);
    tft.setTextColor(TFT_DARKGREEN);
    tft.drawString(text1, x + 5, y + 1);
    tft.drawString(text2, x + 5, y + 17);
  } else {
    tft.fillRoundRect(x, y, 32, 32, 5, TFT_DARKGREEN);
  }
}


// ************************* DASHBOARD ******************************* //

// draw dashboard element (sensor panels)
void drawDashboardElem(Screen type, String heading, int headingX, int headingY, int max, int min, int value, int valueX, int valueY, String unit, int unitX, int unitY) {
  
  tft.fillRect(valueX, valueY, 55 ,30, TFT_BLACK);   // clear previous value text
  
  tft.setTextSize(2);                                // set text size to 2
  tft.setTextColor(TFT_WHITE);                       // set text color to white
  tft.drawString(heading, headingX, headingY);       // draw sensor heading
  tft.setTextSize(3);                                // set text size to 3

  if(type == VIB) {                                  // check if element type is vibration
    if(value == 0) {                                 // if so, check if vib sensor value is positive
      tft.setTextColor(TFT_RED);                     // if so, set text color to red
      tft.drawString("Yes", valueX, valueY);         // print affirmative String reading
    } else {
      tft.drawString("No", 251, 95);                 // else, print negative String reading
    }
  } else {                                           // if any other element type
    if(value > max || value < min) {                 // compare parsed sensor data to user-defined limits
      tft.setTextColor(TFT_RED);                     // set text color to red if sensor value outside of limits
    }
    tft.drawNumber(value, valueX, valueY);           // draw parsed sensor data
    tft.drawString(unit, unitX, unitY);              // draw sensor data unit as a String
  }
}


// draw dashboard (main screen)
void drawDashboardScreen(int temp, int oldTemp, int humi, int oldHumi, int vib, int oldVib, int moist, int oldMoist, int light, int oldLight, int loud, int oldLoud) {

  // draw dashboard separator lines
  tft.fillRect(0,140,320,2,TFT_DARKGREEN);           // draw horizontal line
  tft.fillRect(106,50,2,190,TFT_DARKGREEN);          // draw 1st vertical line    
  tft.fillRect(212,50,2,190,TFT_DARKGREEN);          // draw 2nd veritcal line

  // draw sensor panel elements
  if(temp != oldTemp) {
    drawDashboardElem(TEMP, "Temp", 30, 65, userDefinedRanges[0][0], userDefinedRanges[0][1], temp, 25, 95, "C", 65, 95);
  }
  if(humi != oldHumi) {
    drawDashboardElem(HUMI, "Humi", 140, 65, userDefinedRanges[1][0], userDefinedRanges[1][1], humi, 115, 95, "%RH", 155, 95);
  }
  if(vib != oldVib) {
  drawDashboardElem(VIB, "Vib", 250, 65, NULL, NULL, vib, 242, 95, "", NULL, NULL);
  }
  if(moist != oldMoist) {
    drawDashboardElem(MOIST, "Moist", 25, 160, userDefinedRanges[2][0], userDefinedRanges[5][1], moist, 30, 190, "%", 70, 190);
  }
  if(light != oldLight) {
    drawDashboardElem(LIGHT, "Light", 134, 160, userDefinedRanges[3][0], userDefinedRanges[3][1], light, 135, 190, "%", 175, 190);
  }
  if(loud != oldLoud) {
    drawDashboardElem(LOUD, "Loud", 245, 160, userDefinedRanges[4][0], userDefinedRanges[4][1], loud, 240, 190, "%", 280, 190);
  }
}


// ************************ SENSOR SCREENS *************************** //

// draw status data (common for all individual sensor screens)
void drawStatus(int value, int max, int min) {             
  tft.fillRect(160, 175, 100, 15, TFT_BLACK);        // clear previous status text       
  tft.setTextSize(2);                                // set text size
  tft.setTextColor(TFT_WHITE);                       // set text color to white
  tft.drawString("STATUS:",60,175);                  // draw "STATUS" String
  if(value > max) {                                  // check if sensor value exceeds max limit
    tft.setTextColor(TFT_RED);                       // if so, set text color to red
    tft.drawString("TOO HIGH", 160,175);             // draw String "TOO HIGH" 
  } else if (value < min) {                          // check if sensor value below min limit
    tft.setTextColor(TFT_RED);                       // if so, set text color to red
    tft.drawString("TOO LOW", 172,175);              // draw String "TOO LOW" 
  } else {                                           // if sensor value within desirable range
    tft.setTextColor(TFT_GREEN);                     // set text color to green
    tft.drawString("OK",200,175);                    // draw String "OK"
  }
}


// draw individual sensor screens, which can be cycled through using button inputs
void drawSensorScreen(Screen type, String heading, int headingX, int headingY, int max, int min, int value, int valueX, int valueY, String unit, int unitX, int unitY) {

  tft.fillRect(valueX, valueY, 55, 30, TFT_BLACK);   // clear previous value text

  tft.setTextSize(3);                                // set text size to 3                    
  tft.setTextColor(TFT_WHITE);                       // set text color to white
  tft.drawString(heading, headingX, headingY);       // draw sensor heading

  if(type == VIB) {                                  // check if screen type is vibration                
    if(value == 0) {                                 // if so, check if vib sensor value is positive
      tft.fillRect(80, 115, 160, 65, TFT_BLACK);     // clear previous value text
      tft.setTextColor(TFT_RED);                     // if so, set text color to red
      tft.drawString("Vibrating",80,115);            // print affirmative String reading
    } else {
      tft.fillRect(80, 115, 160, 30, TFT_BLACK);     // clear previous value text
      tft.setTextColor(TFT_GREEN);                   // else, set text color to green
      tft.drawString("NOT",135,115);                 // draw String "NOT"
      tft.setTextColor(TFT_WHITE);                   // set text color to white
      tft.drawString("Vibrating",80,155);            // draw String "VIBRATING"
    }
  } else {                                           // if any other screen type
    if(value > max || value < min) {                 // compare parsed sensor data to user-defined limits
      tft.setTextColor(TFT_RED);                     // set text color to red if sensor value outside of limits
    }
    tft.drawNumber(value,valueX,valueY);             // draw parsed sensor data
    tft.drawString(unit, unitX, unitY);              // draw sensor data unit as a String
    drawStatus(value, max, min);                     // call function to draw status message
  }

  drawTriangles();                                   // call function to draw triangle graphics
} 


// ******************** CONNECTIVITY SCREENS ************************* //

void drawUpdateScreen() {
  clearScreen();                                     // call function to clear screen

  tft.setTextSize(3);                                // set text size to 3                    
  tft.setTextColor(TFT_WHITE);                       // set text color to white
  char* text = "Sensor ranges";
  tft.drawString(text, getCenterX(text), 70);

  text = "received!";
  tft.drawString(text, getCenterX(text), 103);

  tft.setTextColor(TFT_YELLOW);
  text = "UPDATING";
  tft.drawString(text, getCenterX(text), 150);

  tft.setTextColor(TFT_WHITE);
  for(int i = 0; i < 48; i++) {
    tft.drawString(".", 80 + (i*3), 180);
    delay(30);
  }
  delay(1750);                                       // call function to clear screen
  goPrevScreen(screen);                              // call function to return to last screen before sensor range update
}


void drawConnSelectScreen(bool isStartup) {
  char* text = "";
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE);
  if(isStartup) {
    text = "Welcome!";
  } else if(wifiWasConnected && !wifiConnected()) {
    text = "WiFi conn. lost!";
  } else if(mqttWasConnected && !mqttConnected()) {
    text = "MQTT conn. lost!";
  }
  tft.drawString(text, getCenterX(text), 63);

  //char fullText[15];
  //strcpy(fullText, ((wifiWasConnected || mqttWasConnected) ? "Restart MQTT" : "Start MQTT"));
  //const char* fullText = wasConnected ? "Restart MQTT" : "Start MQTT";
  char* fullText;
  if(wifiWasConnected || mqttWasConnected) {
    fullText = "Restart MQTT";
    text = "Restart";
  } else {
    fullText = "Start MQTT";
    text = "Start";
  }
  
  int length = strlen(text) * CHAR_WIDTH;
  tft.drawString(text, getCenterX(fullText), 95);

  tft.setTextColor(TFT_YELLOW);
  text = "MQTT";
  tft.drawString(text, getCenterX(fullText) + length + CHAR_WIDTH, 95);
  
  tft.setTextColor(TFT_WHITE);
  text = "connection?";
  tft.drawString(text, getCenterX(text), 127);

  tft.fillTriangle(55, 180, 55, 200, 35, 190, TFT_WHITE);     // draw left triangle 
  tft.setTextColor(TFT_RED);
  tft.drawString("No", 65, 180);
  tft.fillTriangle(265, 180, 265, 200, 285, 190, TFT_WHITE);  // draw right triangle 
  tft.setTextColor(TFT_GREEN);
  tft.drawString("Yes", 207, 179);
}


void drawConnectScreen(char* connectType, const char* connectValue) {
  clearScreen();

  char* text;
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE);
  text = "Connecting to";
  tft.drawString(text, getCenterX(text), 73);
  
  text = connectType;
  tft.drawString(text, getCenterX(text), 105);
  
  tft.setTextColor(TFT_YELLOW);
  text = toString(connectValue);   
  tft.drawString(text, getCenterX(text), 137);

  drawDotDotDot(strlen(text), getCenterX(text), 169);
}


void drawConnectedText() {
  tft.fillRect(0, 169, WIDTH, CHAR_HEIGHT, TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  char* text = "Connected!";
  tft.drawString(text, getCenterX(text), 169);
}


// **************************** GENERAL ****************************** //

// general function that draws all screens, called directly from main program loop
void drawScreen(int temp, int humi, int vib, int moist, int light, int loud, bool isStartup) {

  // draw header element indicating connection status
  drawConnStatus(wifiConnected(), "Wi", "Fi", 18, 10);
  drawConnStatus((wifiConnected() && mqttConnected()), "MQ", "TT", 272, 10);

 /* declare oldValue variables to track sensor values from previous interval.
  * current sensor values will only be drawn if they != values from previous interval.
  * oldValues are initialised with out-of-bounds value to ensure current values are always initially drawn after a screen reset */
  static int oldTemp = -1;                        
  static int oldHumi = -1;                        
  static int oldVib = -1;                         
  static int oldMoist = -1;                       
  static int oldLight = -1;                      
  static int oldLoud = -1;

    if(screen != oldScreen) {                        // check if screen state has changed
      clearScreen();                                 // if so, call function to clear screen with a black rectangle
      oldTemp = -1;                                  // change old values to out-of-range value to ensure current values are redrawn (see above)
      oldHumi = -1;
      oldVib = -1;
      oldMoist = -1;
      oldLight = -1;                      
      oldLoud = -1;
  }

  // draw screen corresponding to current screen state
  switch(screen) {
    case TEMP:
      if(temp != oldTemp) {
        drawSensorScreen(TEMP, "Temperature", 60, 75, userDefinedRanges[0][0], userDefinedRanges[0][1], temp, 132, 115, "C", 172, 115);
      }
      break;
    case HUMI:
      if(humi != oldHumi) {
        drawSensorScreen(HUMI, "Humidity", 87, 75, userDefinedRanges[1][0], userDefinedRanges[1][1], humi, 105, 115, "% RH", 145, 115);
      }
      break;
    case VIB:
      if(vib != oldVib) {
        drawSensorScreen(VIB, "Vibration", 80, 75, NULL, NULL, vib, 135, 115, "", NULL, NULL);
      }
      break; 
    case MOIST:
      if(moist != oldMoist) {
      drawSensorScreen(MOIST, "Moisture", 91, 75, userDefinedRanges[2][0], userDefinedRanges[2][1], moist, 132, 115, "%", 172, 115);
      }
      break;
    case LIGHT:
      if(light != oldLight) {
      drawSensorScreen(LIGHT, "Light", 115, 75, userDefinedRanges[3][0], userDefinedRanges[3][1], light, 132, 115, "%", 172, 115);
      }
      break;
    case LOUD:
      if(loud != oldLoud) {
      drawSensorScreen(LOUD, "Loudness", 91, 75, userDefinedRanges[4][0], userDefinedRanges[4][1], loud, 132, 115, "%", 172, 115);
      }
      break;
    case DASHBOARD:
      drawDashboardScreen(temp, oldTemp, humi, oldHumi, vib, oldVib, moist, oldMoist, light, oldLight, loud, oldLoud);
      break;
    case UPDATE:
      drawUpdateScreen();
      break;
    case CONNECT_SELECT:
      if (screen != oldScreen) {                     // check so static screen isn't unnecessarily redrawn upon itself
        drawConnSelectScreen(isStartup);             // 
      }
      break;
    case CONNECT_WIFI:
      drawConnectScreen("WiFi network:", SSID);
      break;
    case CONNECT_MQTT:
      drawConnectScreen("MQTT server:", SERVER);
      break;
  }

  //update oldValues every interval
  oldTemp = temp;
  oldHumi = humi;
  oldVib = vib;
  oldMoist = moist;
  oldLight = light;
  oldLoud = loud;
}
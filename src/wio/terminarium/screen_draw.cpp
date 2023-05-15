/***************************************************************************************************
 * Terminarium - LCD screen drawing functions
 * File: {@code screen_draw.cpp} [source file]
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#include "screen_draw.h"                             // include corresponding header file

/**
 * General design: every interval, drawScreen() is called from main program loop which calls specific 
 * function to draw whichever screen correpsonds to the current value of Screen screen.
 * Drawing is done directly to the LCD display (not using a buffer), so dynamic screens like dashboard and
 * sensor screens need to clear themselves before new elements can be drawn on top. To prevent this causing
 * a flicker on every interval: 1) the clear is done by drawing smallest possible background-colored rectangle 
 * over the changing element, and 2) old sensor values are kept track of so elements are redrawn only when 
 * they change, or when screen changes. 
 */

// **************************** GENERAL ****************************** //

// general function that draws all screens, called directly from main program loop
void drawScreen(int temp, int humi, int vib, int moist, int light, int loud, bool isStartup) {

  // draw header icon elements indicating wifi & mqtt connection status
  drawConnStatus(wifiConnected(), "Wi", "Fi", 18, 10);     
  drawConnStatus((wifiConnected() && mqttConnected()), "MQ", "TT", 272, 10);  // check both wifi & mqtt to prevent instances of mqtt up & wifi down due to latency

    if(screen != oldScreen) {                        // check if screen state has changed
      clearScreen();                                 // if so, call function to clear screen by drawing black rectangle
  }

  /**
   * oldValue variables track sensor values from previous interval.
   * Current sensor values will only be drawn if they != values from previous interval. 
   */
  static int oldTemp;                       
  static int oldHumi;                   
  static int oldVib;                      
  static int oldMoist;                      
  static int oldLight;                      
  static int oldLoud;

  /**
   * Draw screen corresponding to current screen state.
   * On dynamic screens, sensor values will only be drawn once initially when screen is swapped to (screen != oldScreen), 
   * then again only if displayed sensor values change (value != oldValue). 
   */
  switch(screen) {
    case DASHBOARD:
      drawDashboardScreen(temp, oldTemp, humi, oldHumi, vib, oldVib, moist, oldMoist, light, oldLight, loud, oldLoud);
      break;
    case TEMP:
      if(screen != oldScreen || temp != oldTemp) {
        drawSensorScreen(TEMP, "Temperature", 60, 75, userDefinedRanges[0][0], userDefinedRanges[0][1], temp, 132, 115, "C", 172, 115);
      }
      break;
    case HUMI:
      if(screen != oldScreen || humi != oldHumi) {
        drawSensorScreen(HUMI, "Humidity", 87, 75, userDefinedRanges[1][0], userDefinedRanges[1][1], humi, 105, 115, "% RH", 145, 115);
      }
      break;
    case VIB:
      if(screen != oldScreen || vib != oldVib) {
        drawSensorScreen(VIB, "Vibration", 80, 75, NULL, NULL, vib, 135, 115, "", NULL, NULL);
      }
      break; 
    case MOIST:
      if(screen != oldScreen || moist != oldMoist) {
      drawSensorScreen(MOIST, "Moisture", 91, 75, userDefinedRanges[2][0], userDefinedRanges[2][1], moist, 132, 115, "%", 172, 115);
      }
      break;
    case LIGHT:
      if(screen != oldScreen || light != oldLight) {
      drawSensorScreen(LIGHT, "Light", 115, 75, userDefinedRanges[3][0], userDefinedRanges[3][1], light, 132, 115, "%", 172, 115);
      }
      break;
    case LOUD:
      if(screen != oldScreen || loud != oldLoud) {
      drawSensorScreen(LOUD, "Loudness", 91, 75, userDefinedRanges[4][0], userDefinedRanges[4][1], loud, 132, 115, "%", 172, 115);
      }
      break;
    case CONNECT_SELECT: 
      if(screen != oldScreen) {                      // check so static screen isn't unnecessarily redrawn upon itself 
        drawConnSelectScreen(isStartup);             // draw connect selection screen and inform whether it is startup (to print "Welcome" message)
      }
      break;
    case CONNECT_CONFIRM:
      if(screen != oldScreen) {                      // check so static screen isn't unnecessarily redrawn upon itself 
        drawConnConfirmScreen();                       
      }
      break;
    case CONNECT_WIFI:
      drawConnectScreen("WiFi network:", SSID);      // draw connect wifi screen and pass SSID data to show on screen
      break;
    case CONNECT_MQTT:
      drawConnectScreen("MQTT server:", SERVER);     // draw connect mqtt screen and pass ip address to show on screen
      break;
    case UPDATE:
      drawUpdateScreen();                            
      break;
  }

  // update oldValues
  oldTemp = temp;                       
  oldHumi = humi;                   
  oldVib = vib;                      
  oldMoist = moist;                      
  oldLight = light;                      
  oldLoud = loud;
}


// ************************** HEADER ********************************* //

/**
 * Note: the code for the dashboard and header has been adapted from Seeed Studio's Smart Garden project from the Wio Terminal Classroom video series:
 * Link: https://github.com/lakshanthad/Wio_Terminal_Classroom_Arduino/tree/main/Classroom%2012/Smart_Garden 
 */

// draw header & background for all screens
void drawHeader() {
  tft.fillScreen(TFT_BLACK);                         // fill background with black color
  tft.fillRect(0,0,320,50,TFT_DARKGREEN);            // fill header rectangle with dark green 
  tft.setTextColor(TFT_WHITE);                       // set text color
  tft.setTextSize(3);                                // set text size 
  char* text = "Terminarium";
  tft.drawString(text, getCenterX(text, 3), 14);        // draw header String
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

// draw dashboard (main screen)
void drawDashboardScreen(int temp, int oldTemp, int humi, int oldHumi, int vib, int oldVib, int moist, int oldMoist, int light, int oldLight, int loud, int oldLoud) {

  // draw dashboard separator lines
  tft.fillRect(0,140,320,2,TFT_DARKGREEN);           // draw horizontal line
  tft.fillRect(106,50,2,190,TFT_DARKGREEN);          // draw 1st vertical line    
  tft.fillRect(212,50,2,190,TFT_DARKGREEN);          // draw 2nd veritcal line

  // draw sensor panel elements (once initially, then again only if individual sensor data changes)
  if(screen != oldScreen || temp != oldTemp) {
    drawDashboardElem(TEMP, "Temp", 30, 65, userDefinedRanges[0][0], userDefinedRanges[0][1], temp, 25, 95, "C", 65, 95);
  }
  if(screen != oldScreen || humi != oldHumi) {
    drawDashboardElem(HUMI, "Humi", 140, 65, userDefinedRanges[1][0], userDefinedRanges[1][1], humi, 115, 95, "%RH", 155, 95);
  }
  if(screen != oldScreen ||vib != oldVib) {
  drawDashboardElem(VIB, "Vib", 250, 65, NULL, NULL, vib, 242, 95, "", NULL, NULL);
  }
  if(screen != oldScreen ||moist != oldMoist) {
    drawDashboardElem(MOIST, "Moist", 25, 160, userDefinedRanges[2][0], userDefinedRanges[5][1], moist, 30, 190, "%", 70, 190);
  }
  if(screen != oldScreen ||light != oldLight) {
    drawDashboardElem(LIGHT, "Light", 134, 160, userDefinedRanges[3][0], userDefinedRanges[3][1], light, 135, 190, "%", 175, 190);
  }
  if(screen != oldScreen ||loud != oldLoud) {
    drawDashboardElem(LOUD, "Loud", 245, 160, userDefinedRanges[4][0], userDefinedRanges[4][1], loud, 240, 190, "%", 280, 190);
  }
}

// draw dashboard element (sensor panels)
void drawDashboardElem(Screen type, String heading, int headingX, int headingY, int min, int max, int value, int valueX, int valueY, String unit, int unitX, int unitY) {
  
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
    if(value < min || value > max) {                 // compare parsed sensor data to user-defined limits
      tft.setTextColor(TFT_RED);                     // set text color to red if sensor value outside of limits
    }
    tft.drawNumber(value, valueX, valueY);           // draw parsed sensor data
    tft.drawString(unit, unitX, unitY);              // draw sensor data unit as a String
  }
}


// ************************ SENSOR SCREENS *************************** //

// draw individual sensor screens, which can be cycled through using button inputs
void drawSensorScreen(Screen type, String heading, int headingX, int headingY, int min, int max, int value, int valueX, int valueY, String unit, int unitX, int unitY) {

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
    if(value < min || value > max) {                 // compare parsed sensor data to user-defined limits
      tft.setTextColor(TFT_RED);                     // set text color to red if sensor value outside of limits
    }
    tft.drawNumber(value,valueX,valueY);             // draw parsed sensor data
    tft.drawString(unit, unitX, unitY);              // draw sensor data unit as a String
    drawStatus(value, min, max);                     // call function to draw status message
  }

  drawTriangles();                                   // call function to draw triangle graphics
} 

// draw status data (common for all individual sensor screens)
void drawStatus(int value, int min, int max) {             
  tft.fillRect(160, 175, 100, 15, TFT_BLACK);        // clear previous status text       
  tft.setTextSize(2);                                // set text size
  tft.setTextColor(TFT_WHITE);                       // set text color to white
  tft.drawString("STATUS:",60,175);                  // draw "STATUS" String
  if(value < min) {                                  // check if sensor value exceeds max limit
    tft.setTextColor(TFT_RED);                       // if so, set text color to red
    tft.drawString("TOO LOW", 172,175);              // draw String "TOO LOW" 
  } else if (value > max) {                          // check if sensor value below min limit
    tft.setTextColor(TFT_RED);                       // if so, set text color to red
    tft.drawString("TOO HIGH", 160,175);             // draw String "TOO HIGH" 
  } else {                                           // if sensor value within desirable range
    tft.setTextColor(TFT_GREEN);                     // set text color to green
    tft.drawString("OK",200,175);                    // draw String "OK"
  }
}


// ******************** CONNECTIVITY SCREENS ************************* //

// draw screen that prompts user with choice to connect or not
void drawUpdateScreen() {
  clearScreen();                                     // call function to clear screen

  tft.setTextSize(3);                                // set text size to 3                    
  tft.setTextColor(TFT_WHITE);                       // set text color to white
  char* text = "Sensor ranges";
  tft.drawString(text, getCenterX(text, 3), 70);        // draw text 

  text = "received!";
  tft.drawString(text, getCenterX(text, 3), 103);       // draw text

  tft.setTextColor(TFT_YELLOW);
  text = "UPDATING";
  tft.drawString(text, getCenterX(text, 3), 150);       // draw text

  tft.setTextColor(TFT_WHITE);
  for(int i = 0; i < 48; i++) {                      // draw progress bar
    tft.drawString(".", 80 + (i*3), 180);
    delay(30);
  }
  delay(1750);                                       // arbtirary delay
  goPrevScreen(screen);                              // call function to return to last screen before sensor range update
}

// draw screen indicating establishing connection (wifi and mqtt)
void drawConnSelectScreen(bool isStartup) {
  char* text = "";
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE);
  if(isStartup) {                                    // if at startup, print contextual "Welcome" text           
    text = "Welcome!";
  } else if(wifiWasConnected && !wifiConnected()) {  // if wifi previously connected but then disconnected, print contextual text
    text = "WiFi conn. lost!";
  } else if(mqttWasConnected && !mqttConnected()) {  // if mqtt previously connected but then disconnected, print contextual text
    text = "MQTT conn. lost!";
  } else if(wifiConnected() && mqttConnected()) {    // if wifi and mqtt both connected, print contextual text
    text = "Already connected";
  }
  tft.drawString(text, getCenterX(text, 3), 63);

  char* fullText;
  if(wifiWasConnected || mqttWasConnected) {         // if previously connected but then disconnected, print contextual "Restart" text
    fullText = "Restart MQTT";
    text = "Restart";
  } else {                                           // otherwise print regular "Start" text
    fullText = "Start MQTT";                         // fulltext used to calculate the centered x starting position
    text = "Start";                                  // first half of fulltext to be printed in white color
  }
  
  int length = strlen(text) * CHAR_WIDTH_3;
  tft.drawString(text, getCenterX(fullText, 3), 95);    // draw only first half of fulltext but center it as though it were whole fullText

  tft.setTextColor(TFT_YELLOW);
  text = "MQTT";                                     // second half of fullText to be printed in yellow
  tft.drawString(text, getCenterX(fullText, 3) + length + CHAR_WIDTH_3, 95); // draw second half at fullText x starting position + its own size + size of an empty space
  
  tft.setTextColor(TFT_WHITE);
  text = "connection?";
  tft.drawString(text, getCenterX(text, 3), 127);

  tft.fillTriangle(40, 180, 40, 200, 20, 190, TFT_WHITE);     // draw left triangle 
  tft.setTextColor(TFT_RED);
  tft.drawString("No", 50, 180);
  tft.fillTriangle(280, 180, 280, 200, 300, 190, TFT_WHITE);  // draw right triangle 
  tft.setTextColor(TFT_GREEN);
  tft.drawString("Yes", 222, 179);
}

void drawConnConfirmScreen() {
  char* text;
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  text = "Proceed with";
  tft.drawString(text, getCenterX(text, 2), 60);

  text = "these details?";
  tft.drawString(text, getCenterX(text, 2), 84);

  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  text = "SSID:";
  tft.drawString(text, 20, 118);

  tft.setTextColor(TFT_YELLOW);
  int length = strlen(text) * 12;
  tft.drawString(SSID, 20 + length + CHAR_WIDTH_2, 118);

  tft.setTextColor(TFT_WHITE);
  text = "Broker:";
  tft.drawString(text, 20, 142);

  tft.setTextColor(TFT_YELLOW);
  length = strlen(text) * 12;
  tft.drawString(SERVER, 20 + length + CHAR_WIDTH_2, 142);

  tft.setTextSize(3);
  tft.fillTriangle(40, 180, 40, 200, 20, 190, TFT_WHITE);     // draw left triangle 
  tft.setTextColor(TFT_RED);
  tft.drawString("No", 50, 180);
  tft.fillTriangle(280, 180, 280, 200, 300, 190, TFT_WHITE);  // draw right triangle 
  tft.setTextColor(TFT_GREEN);
  tft.drawString("Yes", 222, 179);

  tft.setTextSize(2);
  tft.setTextColor(TFT_YELLOW);
  text = "Modify";
  tft.drawString(text, getCenterX(text, 2), 183);
  tft.fillTriangle(148, 210, 172, 210, 160, 230, TFT_WHITE);
}

// draw wifi or mqtt connection screen depending on screen context
void drawConnectScreen(char* connectType, const char* connectValue) {
  clearScreen();

  char* text;
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE);
  text = "Connecting to";
  tft.drawString(text, getCenterX(text, 3), 73);
  
  text = connectType;
  tft.drawString(text, getCenterX(text, 3), 105);
  
  tft.setTextColor(TFT_YELLOW);
  text = toString(connectValue);   
  tft.drawString(text, getCenterX(text, 3), 137);

  drawDotDotDot(strlen(text), getCenterX(text, 3), 169);
}

// draw green "Connected" text upon establishing conneciton (wifi and mqtt)
void drawConnectedText() {
  tft.fillRect(0, 169, TFT_WIDTH, CHAR_HEIGHT_3, TFT_BLACK);
  tft.setTextSize(3);
  tft.setTextColor(TFT_GREEN);
  char* text = "Connected!";
  tft.drawString(text, getCenterX(text, 3), 169);
}



// *************************** MISC ********************************** //

// function that clears screen for switching screen states
extern void clearScreen() {
  tft.fillRect(0,50,320,TFT_HEIGHT - 50, TFT_BLACK); // clear previous screen by overwriting it with black rectangle
}

// function that calculates centered x starting position for any given text
int getCenterX(char* text, int textSize) {  
  int pixelWidth;              
  if(textSize == 2) {
    pixelWidth = CHAR_WIDTH_2;
  } else if(textSize == 3) {
    pixelWidth = CHAR_WIDTH_3;
  }
  int textWidth = strlen(text) * pixelWidth;         // get text pixel size by multiplying (number of characters in text) x (number of pixels per character)
  int xPosition = (TFT_WIDTH - textWidth) / 2;       // calculate x starting position by (width of screen) - (text pixel size) / 2
  return xPosition;
}

/**
 * @drawTriangles: draw triangle graphics (common in all sensor screens)
 * used to visually communicate that screens can be cycled through using left/right button inputs <..> 
 */
void drawTriangles() {                                        
  tft.fillTriangle(55, 115, 55, 135, 35, 125, TFT_WHITE);     // draw left triangle 
  tft.fillTriangle(260, 115, 260, 135, 280, 125, TFT_WHITE);  // draw right triangle 
}

// draw dot dot dot writing effect when establishing connectivity
void drawDotDotDot(int length, int x, int y) {
  tft.fillRect(0, y, TFT_WIDTH, CHAR_HEIGHT_3, TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  for(int i = 0; i < length; i++) {
    tft.drawString(".", x + (i * CHAR_WIDTH_3), y);
    delay(300);
  }
}
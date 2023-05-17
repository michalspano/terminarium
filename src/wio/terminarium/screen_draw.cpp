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

  if(screen != oldScreen) {                          // check if screen state has changed
    clearScreen();                                   // if so, call function to clear screen by drawing black rectangle
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
    case USER_INPUT_SSID:
      if (screen != oldScreen || buttonPressed) {
        drawInputScreen(inputSSID);
      }
      break;
    case USER_INPUT_PSWD:
      if (screen != oldScreen || buttonPressed) {
        drawInputScreen(inputPSWD);
      }
      break;
    case USER_INPUT_MQTT:
      if (screen != oldScreen || buttonPressed) {
        drawInputScreen(inputMQTT);
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


// ********************* USER INPUT SCREENS ************************** //

// function to draw user input screen and its components
void drawInputScreen(char* userInput) {

  tft.setTextColor(TFT_WHITE);                       // set text color to white
  tft.setTextSize(2);                                // set text size

  char* fullText;                                    // declare address to store fullText (used to calculate the centered x starting position)
  if(screen == USER_INPUT_SSID) {                    
    fullText = "Enter WiFi SSID:";                   // fullText if entering SSID
  } else if (screen == USER_INPUT_PSWD) {
    fullText = "Enter WiFi password:";               // fullText if entering password
  } else if (screen == USER_INPUT_MQTT) {
    fullText = "Enter MQTT address:";                // fullText if entering mqtt broker address
  }
  
  char* text = "Enter";                              // first half of fullText to be printed in white color
  int length = strlen(text) * CHAR_WIDTH_2;          // determine pixel width of first half of fullText
  tft.drawString(text, getCenterX(fullText, 2), 60); // draw only first half of fulltext but center it as though it were whole fullText

  tft.setTextColor(TFT_YELLOW);                      // set text color to yellow
  if(screen == USER_INPUT_SSID) {                    
    text = "WiFi SSID:";                             // second half of fullText if entering SSID
  } else if (screen == USER_INPUT_PSWD) {
    text = "WiFi password:";                         // second half of fullText if entering password
  } else if (screen == USER_INPUT_MQTT) {
    text = "MQTT address:";                          // second half of fullText if entering mqtt broker address
  }
  tft.drawString(text, getCenterX(fullText, 2) + length + CHAR_WIDTH_2, 60); // draw second half at fullText x starting position + its own size + size of an empty space

  tft.fillRect(0, 118, 320, 2, TFT_DARKGREEN);       // draw top keyboard border
  tft.fillRect(0, 230, 320, 2, TFT_DARKGREEN);       // draw bottom keyboard border

  drawKeyboard();                                    // call function to draw the keyboard
  drawSelection();                                   // call function to draw the character currently highlighted on keyboard
  drawUserInput(userInput);                          // call function to draw user inputted String as it is being typed
}

// function to draw keyboard
void drawKeyboard() {
  // tft.fillRect(0, 120, 320, 90, TFT_BLACK);
  int x = KEY_X;                                     // assign x position of first keyboard element
  int y = KEY_Y;                                     // assign y position of first keyboard element

  for (int i = 0; i < KEY_COLUMNS; i++) {                                 // loop through keyboard columns 
    tft.drawChar(x, y, keyboard[0][0 + i], TFT_WHITE, TFT_BLACK, 2);      // draw row 1
    tft.drawChar(x, y + 20, keyboard[1][0 + i], TFT_WHITE, TFT_BLACK, 2); // draw row 2
    tft.drawChar(x, y + 40, keyboard[2][0 + i], TFT_WHITE, TFT_BLACK, 2); // draw row 3
    tft.drawChar(x, y + 60, keyboard[3][0 + i], TFT_WHITE, TFT_BLACK, 2); // draw row 4
    x = x + 13;                                                           // increment x value to draw next column
  }
  tft.setTextColor(TFT_WHITE);                       // set text color to white
  tft.setTextSize(2);                                // set text text size

  // draw black rectangle over DEL key to reset its state
  tft.fillRect(KEY_X, KEY_Y + 80, (strlen("DEL") * CHAR_WIDTH_2), CHAR_HEIGHT_2, TFT_BLACK);
  tft.drawString("DEL", KEY_X, KEY_Y + 80); // draw DEL key

  // draw black rectangle over SPACE key to reset its state                          
  tft.fillRect(getCenterX("SPACE", 2), KEY_Y + 80, (strlen("SPACE") * CHAR_WIDTH_2), CHAR_HEIGHT_2, TFT_BLACK);
  tft.drawString("SPACE", getCenterX("SPACE", 2), KEY_Y + 80); // draw SPACE key

  // draw black rectangle over ENTER key to reset its state
  tft.fillRect(TFT_WIDTH - KEY_X - (strlen("ENTER") * CHAR_WIDTH_2), KEY_Y + 80, (strlen("ENTER") * CHAR_WIDTH_2), CHAR_HEIGHT_2, TFT_BLACK);
  tft.drawString("ENTER", TFT_WIDTH - KEY_X - (strlen("ENTER") * CHAR_WIDTH_2), KEY_Y + 80); // draw ENTER key
}

// function to draw character currently highlighted on keyboard
void drawSelection() {
  if (currentChar[0] < KEY_ROWS) { // if currently highlighted key is a character in the top four rows
    // draw the character highlighted in green
    tft.drawChar(currentXY[0], currentXY[1], keyboard[currentChar[0]][currentChar[1]], TFT_GREEN, TFT_DARKGREEN, 2);

  } else { // if currently highlighted key belongs to bottom row
    tft.setTextColor(TFT_GREEN); // set text color to green

    if (currentChar[1] < 6) {    // if key is on left side of screen
      // draw the green highlight rectangle behind DEL key
      tft.fillRect(KEY_X, KEY_Y + 80, (strlen("DEL") * CHAR_WIDTH_2), CHAR_HEIGHT_2, TFT_DARKGREEN);
      // draw the DEL key highlighted in green
      tft.drawString("DEL", KEY_X, KEY_Y + 80);
    }
    if (currentChar[1] > 5 && currentChar[1] < 16) { // if currently highlighted key is in center of screen
      // draw green highlight rectangle behind SPACE key
      tft.fillRect(getCenterX("SPACE", 2), KEY_Y + 80, (strlen("SPACE") * CHAR_WIDTH_2), CHAR_HEIGHT_2, TFT_DARKGREEN);
      // draw the SPACE key highlighted in green
      tft.drawString("SPACE", getCenterX("SPACE", 2), KEY_Y + 80);
    }
    if (currentChar[1] > 15) { // if currently highlighted key is on right side of screen
      // draw green highlight rectangle behind ENTER key
      tft.fillRect(TFT_WIDTH - KEY_X - (strlen("ENTER") * CHAR_WIDTH_2), KEY_Y + 80, (strlen("ENTER") * CHAR_WIDTH_2), CHAR_HEIGHT_2, TFT_DARKGREEN);
      // draw the ENTER key highlighted in green
      tft.drawString("ENTER", TFT_WIDTH - KEY_X - (strlen("ENTER") * CHAR_WIDTH_2), KEY_Y + 80);
    }
  }
}

// draw user inputted String as it being typed
void drawUserInput(char* userInput) {
  if (buttonPressed) {                               // if button has been pressed while in user input screen           
    tft.setTextColor(TFT_YELLOW);                    // set text color to yellow
    tft.setTextSize(3);                              // set text size
    tft.fillRect(0, 85, TFT_WIDTH, CHAR_HEIGHT_3, TFT_BLACK); // draw black rectangle to cover previous outdated Stringg
    tft.drawString(userInput, getCenterX(userInput, 3), 85);  // rerdraw newly updated input String
    buttonPressed = false;                           // revert button pressed flag to false
  }  
}

// ******************** CONNECTIVITY SCREENS ************************* //

// draw screen that prompts user with choice to connect or not
void drawUpdateScreen() {
  clearScreen();                                     // call function to clear screen

  tft.setTextSize(3);                                // set text size to 3                    
  tft.setTextColor(TFT_WHITE);                       // set text color to white
  char* text = "Sensor ranges";
  tft.drawString(text, getCenterX(text, 3), 70);     // draw centered text 

  text = "received!";
  tft.drawString(text, getCenterX(text, 3), 103);    // draw centered text

  tft.setTextColor(TFT_YELLOW);                      // set text color to yellow
  text = "UPDATING";
  tft.drawString(text, getCenterX(text, 3), 150);    // draw centered text

  tft.setTextColor(TFT_WHITE);                       // set text color to white
  for(int i = 0; i < 48; i++) {                      // loop to draw progress bar
    tft.drawString(".", 80 + (i*3), 180);            // print a '.' character in quick succession
    delay(30);                                       // delay determining progress bar speed
  }
  delay(1750);                                       // arbitrary delay
  goPrevScreen(screen);                              // call function to return to last screen before sensor range update
}

// draw screen indicating establishing connection (wifi and mqtt)
void drawConnSelectScreen(bool isStartup) {
  char* text = "";                                   // declare text as blank in case none of the conditions below apply
  tft.setTextSize(3);                                // set text size
  tft.setTextColor(TFT_WHITE);                       // set text color to white
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
  tft.drawString(text, getCenterX(fullText, 3), 95); // draw only first half of fulltext but center it as though it were whole fullText

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

// draw screen to confirm that network info is correct
void drawConnConfirmScreen() {
  char* text;                                        
  tft.setTextSize(2);                                // set text size 
  tft.setTextColor(TFT_WHITE);                       // set text color to white
  text = "Proceed with";
  tft.drawString(text, getCenterX(text, 2), 60);     // draw text, first line

  text = "these details?";
  tft.drawString(text, getCenterX(text, 2), 84);     // draw text, second line

  text = "SSID:";                         
  tft.drawString(text, 20, 118);                     // draw SSID heading

  tft.setTextColor(TFT_YELLOW);                      // set text color to yellow
  int length = strlen(text) * 12;                    // determine pixel width of heading text
  tft.drawString(SSID, 20 + length + (CHAR_WIDTH_2 / 2), 118); // draw current SSID value

  tft.setTextColor(TFT_WHITE);                       // set text color to white
  text = "Broker:";
  tft.drawString(text, 20, 142);                     // draw mqtt address heading

  tft.setTextColor(TFT_YELLOW);                      // set text color to yellow
  length = strlen(text) * 12;                        // determine pixel width of heading text
  tft.drawString(SERVER, 20 + length + (CHAR_WIDTH_2 / 2), 142); // draw current mqtt address value

  tft.setTextSize(3);                                         // set text size
  tft.fillTriangle(40, 180, 40, 200, 20, 190, TFT_WHITE);     // draw left triangle indicating user can go back 
  tft.setTextColor(TFT_RED);                                  // set text color to red
  tft.drawString("No", 50, 180);                              // draw "No" next to left triangle
  tft.fillTriangle(280, 180, 280, 200, 300, 190, TFT_WHITE);  // draw right triangle indicating user can proceed with connection
  tft.setTextColor(TFT_GREEN);                                // set text color to green
  tft.drawString("Yes", 222, 179);                            // draw "Yes" next to right triangle

  tft.setTextSize(2);                                         // set text size
  tft.setTextColor(TFT_YELLOW);                               // set text color to yellow
  tft.fillTriangle(148, 210, 172, 210, 160, 230, TFT_WHITE);  // draw downward facing triangle indicating user can modify network info
  text = "Modify";
  tft.drawString(text, getCenterX(text, 2), 183);             // draw centered "No" above downward facing triangle
}

// draw wifi or mqtt connection screen depending on screen context
void drawConnectScreen(char* connectType, const char* connectValue) {
  char* text;
  tft.setTextSize(3);                                         // set text size 
  tft.setTextColor(TFT_WHITE);                                // set text color to white
  text = "Connecting to";
  tft.drawString(text, getCenterX(text, 3), 73);              // draw centered text
  
  text = connectType;                                         // assign current connection context (wifi or moqtt) to a text variable
  tft.drawString(text, getCenterX(text, 3), 105);             // draw centered text variable
  
  tft.setTextColor(TFT_YELLOW);                               // set text color to yellow
  text = toString(connectValue);                              // assign current value of network info (wifi or mqtt)
  tft.drawString(text, getCenterX(text, 3), 137);             // draw centered current value of network info

  drawDotDotDot(strlen(text), getCenterX(text, 3), 169);      // draw dot..dot...dot animation indicating currently connecting
}

// draw green "Connected" text upon establishing conneciton (wifi and mqtt)
void drawConnectedText() {
  tft.fillRect(0, 169, TFT_WIDTH, CHAR_HEIGHT_3, TFT_BLACK);  // draw black rectangle to overwrite dot...dot...dot progress indicator
  tft.setTextSize(3);                                         // set text size
  tft.setTextColor(TFT_GREEN);                                // set text color to green
  char* text = "Connected!";
  tft.drawString(text, getCenterX(text, 3), 169);             // draw centered 'Connected' message
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
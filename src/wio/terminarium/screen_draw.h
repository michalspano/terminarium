/***************************************************************************************************
 * Terminarium - LCD screen drawing functions
 * File: {@code screen_draw.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

/* Note: the code for the dashboard and header has been adapted from Seeed Studio's Smart Garden project from the Wio Terminal Classroom video series:
* Link: https://github.com/lakshanthad/Wio_Terminal_Classroom_Arduino/tree/main/Classroom%2012/Smart_Garden */

// define acceptable sensor value boundaries
#define MAX_LIMIT 75
#define MIN_LIMIT 25

extern TFT_eSPI tft;                            // include wio terminal LCD screen variable in current scope 
extern Screen screen;                           // include global screen state variable in current scope 


// ************************** HEADER ********************************* //

// draw headder & background for all screens
void drawHeader() {
  tft.fillScreen(TFT_BLACK);                    // fill background with black color
  tft.fillRect(0,0,320,50,TFT_DARKGREEN);       // fill header rectangle with dark green 
  tft.setTextColor(TFT_WHITE);                  // set text color
  tft.setTextSize(3);                           // set text size 
  tft.drawString("Terminarium",60,15);          // draw header String
}


// ************************* DASHBOARD ******************************* //

// draw dashboard element (sensor panels)
void drawDashboardElem(Screen type, String heading, int headingX, int headingY, int max, int min, int value, int valueX, int valueY, String unit, int unitX, int unitY) {
  tft.setTextSize(2);                           // set text size to 2
  tft.setTextColor(TFT_WHITE);                  // set text color to white
  tft.drawString(heading, headingX, headingY);  // draw sensor heading
  tft.setTextSize(3);                           // set text size to 3

  if(type == VIB) {                             // check if element type is vibration
    if(value == 0) {                            // if so, check if vib sensor value is positive
      tft.setTextColor(TFT_RED);                // if so, set text color to red
      tft.drawString("Yes",242,95);             // print affirmative String reading
    } else {
      tft.drawString("No",251,95);              // else, print negative String reading
    }
  } else {                                      // if any other element type
    if(value > max || value < min) {            // compare parsed sensor data to user-defined limits
      tft.setTextColor(TFT_RED);                // set text color to red if sensor value outside of limits
    }
    tft.drawNumber(value, valueX, valueY);      // draw parsed sensor data
    tft.drawString(unit, unitX, unitY);         // draw sensor data unit as a String
  }
}


// draw dashboard (main screen)
void drawDashboardScreen(int temp, int humi, int vib, int moist, int light, int loud) {
 
  tft.fillRect(0,50,320,TFT_HEIGHT - 50, TFT_BLACK);          // overwrite previous screen with black

  // draw dashboard separator lines
  tft.drawFastVLine(106,50,190,TFT_DARKGREEN);  // draw 1st vertical line
  tft.drawFastVLine(212,50,190,TFT_DARKGREEN);  // draw 2nd veritcal line
  tft.drawFastHLine(0,140,320,TFT_DARKGREEN);   // draw horizontal line

  // draw sensor panel elements
  drawDashboardElem(TEMP, "Temp", 30, 65, MAX_LIMIT, MIN_LIMIT, temp, 25, 95, "C", 65, 95);
  drawDashboardElem(HUMI, "Humi", 140, 65, MAX_LIMIT, MIN_LIMIT, humi, 115, 95, "%RH", 155, 95);
  drawDashboardElem(VIB, "Vib", 250, 65, NULL, NULL, vib, NULL, NULL, "", NULL, NULL);
  drawDashboardElem(MOIST, "Moist", 25, 160, MAX_LIMIT, MIN_LIMIT, moist, 30, 190, "%", 70, 190);
  drawDashboardElem(LIGHT, "Light", 134, 160, MAX_LIMIT, MIN_LIMIT, light, 135, 190, "%", 175, 190);
  drawDashboardElem(LOUD, "Loud", 245, 160, MAX_LIMIT, MIN_LIMIT, loud, 240, 190, "%", 280, 190);
}


// ************************ SENSOR SCREENS *************************** //

// draw status data (common for all individual sensor screens)
void drawStatus(int value) {                    
  tft.setTextSize(2);                           // set text size
  tft.setTextColor(TFT_WHITE);                  // set text color to white
  tft.drawString("STATUS:",60,175);             // draw "STATUS" String
  if(value > MAX_LIMIT) {                       // check if sensor value exceeds max limit
    tft.setTextColor(TFT_RED);                  // if so, set text color to red
    tft.drawString("TOO HIGH", 160,175);        // draw String "TOO HIGH" 
  } else if (value < MIN_LIMIT) {               // check if sensor value below min limit
    tft.setTextColor(TFT_RED);                  // if so, set text color to red
    tft.drawString("TOO LOW", 172,175);         // draw String "TOO LOW" 
  } else {                                      // if sensor value within desirable range
    tft.setTextColor(TFT_GREEN);                // set text color to green
    tft.drawString("OK",200,175);               // draw String "OK"
  }
}


/* draw triangle graphics (common in all sensor screens)
 * used to visually communicate that screens can be cycled through using left/right button inputs <..> */
void drawTriangles() {                                        
  tft.fillTriangle(55, 115, 55, 135, 35, 125, TFT_WHITE);     // draw left triangle 
  tft.fillTriangle(260, 115, 260, 135, 280, 125, TFT_WHITE);  // draw right triangle 
}


// draw individual sensor screens, which can be cycled through using button inputs
void drawSensorScreen(Screen type, String heading, int headingX, int headingY, int max, int min, int value, int valueX, int valueY, String unit, int unitX, int unitY) {

  tft.fillRect(0,50,320,TFT_HEIGHT - 50, TFT_BLACK);          // overwrite previous screen with black

  tft.setTextSize(3);                           // set text size to 3                    
  tft.setTextColor(TFT_WHITE);                  // set text color to white
  tft.drawString(heading, headingX, headingY);  // draw sensor heading

  if(type == VIB) {                             // check if screen type is vibration                
    if(value == 0) {                            // if so, check if vib sensor value is positive
      tft.setTextColor(TFT_RED);                // if so, set text color to red
      tft.drawString("Vibrating",80,115);       // print affirmative String reading
    } else {
      tft.setTextColor(TFT_GREEN);              // else, set text color to green
      tft.drawString("NOT",135,115);            // draw String "NOT"
      tft.setTextColor(TFT_WHITE);              // set text color to white
      tft.drawString("Vibrating",80,155);       // draw String "VIBRATING"
    }
  } else {                                      // if any other screen type
    if(value > max || value < min) {            // compare parsed sensor data to user-defined limits
      tft.setTextColor(TFT_RED);                // set text color to red if sensor value outside of limits
    }
    tft.drawNumber(value,valueX,valueY);        // draw parsed sensor data
    tft.drawString(unit, unitX, unitY);         // draw sensor data unit as a String
    drawStatus(value);                          // call function to draw status message
  }

  drawTriangles();                              // call function to draw triangle graphics
} 


// **************************** GENERAL ****************************** //

// general function that draws all screens, called directly from main program loop
void drawScreen(int temp, int humi, int vib, int moist, int light, int loud) {

  // draw screen corresponding to current screen state
  switch(screen) {
    case TEMP:
      drawSensorScreen(TEMP, "Temperature", 60, 75, MAX_LIMIT, MIN_LIMIT, temp, 132, 115, "C", 172, 115);
      break;
    case HUMI:
      drawSensorScreen(HUMI, "Humidity", 87, 75, MAX_LIMIT, MIN_LIMIT, humi, 105, 115, "% RH", 145, 115);
      break;
    case VIB:
      drawSensorScreen(VIB, "Vibration", 80, 75, NULL, NULL, vib, NULL, NULL, "", NULL, NULL);
      break; 
    case MOIST:
      drawSensorScreen(MOIST, "Moisture", 91, 75, MAX_LIMIT, MIN_LIMIT, moist, 132, 115, "%", 172, 115);
      break;
    case LIGHT:
      drawSensorScreen(LIGHT, "Light", 115, 75, MAX_LIMIT, MIN_LIMIT, light, 132, 115, "%", 172, 115);
      break;
    case LOUD:
      drawSensorScreen(LOUD, "Loudness", 91, 75, MAX_LIMIT, MIN_LIMIT, loud, 132, 115, "%", 172, 115);
      break;
    default:
      drawDashboardScreen(temp, humi, vib, moist, light, loud);
      break;
  }
}
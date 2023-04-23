//Libraries 
#include "TFT_eSPI.h" //TFT LCD library 

TFT_eSPI tft; //Initializing TFT LCD
TFT_eSprite spr = TFT_eSprite(&tft); //Initializing buffer

#include "screen_control.h" // import screen controller
#include "screen_draw.h"    // import screen functions

Screen screen;

void setup() {
  Serial.begin(9600); //Start serial communication
  
  // Set buttons as input
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_A), goNextScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_C), goPrevScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_B), goDashScreen, FALLING);
  
  tft.begin(); //Start TFT LCD
  tft.setRotation(3); //Set TFT LCD rotation
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH); //Create buffer
}

int i = 0;

void loop() {
  int t = 76;       //Assign variable to store temperature 
  int h = 50;       //Assign variable to store humidity 
  int v = 1;        //Assign variable to store vibration
  int m = 75;       //Assign variable to store moisture
  int li = 21;      //Assign variable to store light sensor value
  int lo = 10;      //Assign variable to store loudness sensor value

  // Toggles
  if(i % 2 == 0) {
    v = 0;
    t = 25;
    h = 76;
    m = 22;
    li = 99;
    lo = 50;
  }
  i++;

  drawScreen(t, h, v, m, li, lo);

  spr.pushSprite(0,0); //Push to LCD

  delay(1000); 
}


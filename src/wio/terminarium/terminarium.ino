/***************************************************************************************************
 * Terminarium
 * File: {@code terminarium.ino}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda, 
 *          Konstantinos Rokanas, Jonathan Boman
 * 
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

// declare imports
#include "DHT_Async.h"                    // import DHT library
#include "pins.h"                         // import pins for sensors
#include "utils.h"                        // import utility functions
#include "TFT_eSPI.h"                     // import TFT LCD library 
#include "screen_control.h"               // import screen controller functions
#include "screen_draw.h"                  // import screen drawing functions

// initializations
DHT_Async dht(DHT_PIN, DHTTYPE);          // initialise temp&humi sensor-struct
TFT_eSPI tft;                             // declare terminal LCD
TFT_eSprite spr = TFT_eSprite(&tft);      // initialise screen buffer using sprite function
Screen screen;                            // declare variable storing current screen

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);         // enable the serial monitor
  pinMode(VIBRATION_PIN, INPUT);          // set up vibration sensor
  tft.begin();                            // start terminal LCD
  tft.setRotation(3);                     // set terminal LCD rotation
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH); // create screen buffer

  // set buttons as input - interrupt program to cycle through screens on button press
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_A), goNextScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_C), goPrevScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_B), goDashScreen, FALLING);
}

void loop() {

  // ***************************** READING ********************************************* //

  float* tempHumiVal    = readTempHumi();                 // read temp & humi signal
  int vibSignal         = digitalRead(VIBRATION_PIN);     // read vibration signal
  int moistureSignal    = analogRead(MOISTURE_PIN);       // read moisture signal
  int lightSignal       = analogRead(LIGHT_PIN);          // read light signal
  int loudnessSignal    = analogRead(LOUDNESS_PIN);       // read loudness signal

  // ********************************* PARSING ******************************************* //

  float temp            = tempHumiVal[0];
  float humi            = tempHumiVal[1];
  String vibResult      = parseVibrationValue(vibSignal);
  int moistureResult    = mapToPercentage(moistureSignal);
  int lightResult       = mapToPercentage(lightSignal);
  int loudnessResult    = mapToPercentage(loudnessSignal);

  // ***************************** PRINTING (serial monitor) ***************************** //
  
  if(intervalPassed()) {                                  // run code if desired interval (in ms) has elapsed

    Serial.printf("Temperature: %.2f°C\n", temp);         // temperature in Celcius
    Serial.printf("Humidity: %.2f%%RH\n", humi);          // humidity in percentage
    Serial.printf("Vibration: %s\n", vibResult.c_str());  // vibration as string state
    Serial.printf("Moisture: %d%%\n", moistureResult);    // moisture in percentage
    Serial.printf("Light level: %d%%\n", lightResult);    // light in percentage
    Serial.printf("Loudness: %d%%\n", loudnessResult);    // loudness in percentage

    SEPARATOR;                                            // visual separator for serial monitor

  // ******************************* DRAWING (LCD screen) ******************************** //

    drawScreen(temp, humi, vibSignal, moistureResult, lightResult, loudnessResult);  // draw screen graphics on LCD
    spr.pushSprite(0,0);                                  // push sprite to LCD
  }                     
}

/***************************************************************************************************
 * Terminarium
 * File: {@code terminarium.ino}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda, 
 *          Konstantinos Rokanas, Jonathan Boman
 * 
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

// declare imports
#include "DHT.h"                          // import DHT library
#include "pins.h"                         // import pins for sensors
#include "utils.h"                        // import utility functions
#include "TFT_eSPI.h"                     // import TFT LCD library 
#include "screen_control.h"               // import screen controller functions
#include "screen_draw.h"                  // import screen drawing functions

// initializations
DHT dht(DHT_PIN, DHTTYPE);                // initialise temp&humi sensor-struct
TFT_eSPI tft;                             // initialise terimnal LCD
TFT_eSprite spr = TFT_eSprite(&tft);      // initialise screen buffer using sprite function
Screen screen;                            // initialise variable storing current screen

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);         // enable the serial monitor
  pinMode(VIBRATION_PIN, INPUT);          // set up vibration sensor (digital)
  dht.begin();                            // initialise temp&humi sensor (digital)
  tft.begin();                            // start terminal LCD
  tft.setRotation(3);                     // set terminal LCD rotation
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH); // create buffer

  // set buttons as input
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_A), goNextScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_C), goPrevScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_B), goDashScreen, FALLING);
}

void loop() {
  /* Note: the temperature/humidity code sample has been adapted from the DHT library example:
   * Link: https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor/blob/master/examples/DHTtester/DHTtester.ino */

  // ***************************** READING ********************************************* //

  float tempHumiVal[2] = {};                        // initialise array for temp&humi values
  dht.readTempAndHumidity(tempHumiVal);             // read temp&humi sensor

  int vibSignal       = digitalRead(VIBRATION_PIN); // read vibration signal
  int moistureSignal  = analogRead(MOISTURE_PIN);   // read moisture signal
  int lightSignal     = analogRead(LIGHT_PIN);      // read light signal
  int loudnessSignal  = analogRead(LOUDNESS_PIN);   // read loudness signal

  // ********************************* PARSING ******************************************* //

  float temp            = tempHumiVal[1];
  float humi            = tempHumiVal[0];
  String vibResult      = parseVibrationValue(vibSignal);
  int moistureResult    = mapToPercentage(moistureSignal);
  int lightResult       = mapToPercentage(lightSignal);
  int loudnessResult    = mapToPercentage(loudnessSignal);

  // ***************************** PRINTING (serial monitor) ***************************** //

  Serial.printf("Temperature: %.2f°C\n", temp);         // temperature in Celcius
  Serial.printf("Humidity: %.2f%%RH\n", humi);          // humidity in percentage
  Serial.printf("Vibration: %s\n", vibResult.c_str());  // vibration as string state
  Serial.printf("Moisture: %d%%\n", moistureResult);    // moisture in percentage
  Serial.printf("Light level: %d%%\n", lightResult);    // light in percentage
  Serial.printf("Loudness: %d%%\n", loudnessResult);    // loudness in percentage

  SEPARATOR;           // visual separator for serial monitor

  // ******************************* DRAWING (LCD screen) ******************************** //

  drawScreen(temp, humi, vibSignal, moistureResult, lightResult, loudnessResult);   // draw screen graphics on LCD
  spr.pushSprite(0,0); // push sprite to LCD

  delay(LOOP_DELAY);   // arbitrary delay to make up for the sensors' latency delay
}

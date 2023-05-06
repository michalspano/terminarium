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
#include "screen_control.h"               // import screen controller functions
#include "utils.h"                        // import utility functions
#include "TFT_eSPI.h"                     // import TFT LCD library 
#include "screen_draw.h"                  // import screen drawing functions
#include "mqtt.h"                         // import mqtt functions

// initializations
DHT_Async dht(DHT_PIN, DHTTYPE);          // initialise temp&humi sensor-struct
TFT_eSPI tft;                             // initialise wio terminal LCD
TFT_eSprite spr = TFT_eSprite(&tft);      // initialise screen buffer using sprite function
Screen screen = CONNECT_SELECT;           // initialise variable storing current screen to connection screen
Screen oldScreen;                         // declare variable storing old screen (used for recognising if screen has changed)
bool shouldUpdateOldScreen;               // declare flag if oldScreen should be updated - necessary for some unique draw functions
bool isStartup = true;                    // declare flag that alters connection screen behavior after initialisation

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);         // enable the serial monitor
  pinMode(VIBRATION_PIN, INPUT);          // set up vibration sensor (digital)
  tft.begin();                            // start terminal LCD
  tft.setRotation(3);                     // set terminal LCD rotation

  // set buttons as input
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_A), goRightScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_C), goLeftScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_B), goDashScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_5S_PRESS), goConnSelectScreen, FALLING);

  client.setServer(SERVER, 1883);       // set up mqtt server   
  client.setCallback(callback);         // set up behavior when new message received from mqtt broker

  drawHeader();                           // draw headder & background for all screens
}


void loop() {

  // ******************************* CONNECT MQTT **************************************** //
  
  if(screen == CONNECT_WIFI) {
    drawConnectScreen("WiFi network:", SSID); // draw wifi connection screen
    setupWifi();                          // connect to wifi network
  }
  
  if(screen == CONNECT_MQTT) {
    drawConnectScreen("MQQT server:", SERVER);
    setupClient();                        // connect to mqtt broker
  }
/*
  if(!wifiConnected()) {    // check if connected to wifi network
    drawConnectScreen("WiFi network:", SSID); // draw wifi connection screen
    reconnectWifi();                      // if not, attempt reconnect
  }

  if (!mqttConnected()) {                 // check if connected to mqtt server
    drawConnectScreen("MQQT server:", SERVER);
    reconnectClient();                    // if not, attempt reconnect
  } else {
    client.loop();                          // stay connected and listening to mqtt broker 
  } */
  

  // ********************************* READING ******************************************* //

  float* tempHumiVal    = readTempHumi();                 // read temp & humi signal
  int vibSignal         = digitalRead(VIBRATION_PIN);     // read vibration signal
  int moistureSignal    = analogRead(MOISTURE_PIN);       // read moisture signal
  int lightSignal       = analogRead(LIGHT_PIN);          // read light signal
  int loudnessSignal    = analogRead(LOUDNESS_PIN);       // read loudness signal

  // ********************************* PARSING ******************************************* //

  float temp            = tempHumiVal[0];                  // extract temperature value from tempHumi array 
  int humi              = tempHumiVal[1];                  // extract humidity value from tempHumi array
  char* vibResult       = parseVibrationValue(vibSignal);  // parse vibration value from int to char*
  int moistureResult    = mapToPercentage(moistureSignal); // convert moisture value to a % 
  int lightResult       = mapToPercentage(lightSignal);    // convert light value to a % 
  int loudnessResult    = mapToPercentage(loudnessSignal); // convert loudness value to a % 

  // *************************** PRINTING (serial monitor) ******************************* //

  if(intervalPassed()) {                                   // run code if desired interval (in ms) has elapsed

    // print sensor data to serial monitor
    Serial.printf("Temperature: %.1f°C\n", temp);          // temperature in Celcius
    Serial.printf("Humidity: %d%% RH\n", humi);            // humidity in percentage
    Serial.printf("Vibration: %s\n", vibResult);           // vibration as string state
    Serial.printf("Moisture: %d%%\n", moistureResult);     // moisture in percentage
    Serial.printf("Light level: %d%%\n", lightResult);     // light in percentage
    Serial.printf("Loudness: %d%%\n", loudnessResult);     // loudness in percentage

    SEPARATOR;                                             // visual separator for serial monitor

  // ***************************** DRAWING (LCD screen) ********************************** //

    shouldUpdateOldScreen = true;                          // set to true by default (specific screen draw functions can set it to false) 

    // draw screen graphics on LCD
    drawScreen(temp, humi, vibSignal, moistureResult, lightResult, loudnessResult, isStartup, mqttConnected());                             
    
    if(shouldUpdateOldScreen) {                            // check whether oldScreen value should be updated
      oldScreen = screen;                                  // update oldScreen value, used to determine drawing behavior on next interval
    }
    
  // ********************************** PUBLISHING *************************************** //

    // publish each sensor data to mqtt broker
    client.publish(TOPIC_PUB_TEMP, toString(temp));
    client.publish(TOPIC_PUB_HUMI, toString(humi));
    client.publish(TOPIC_PUB_VIB, vibResult);
    client.publish(TOPIC_PUB_MOIST, toString(moistureResult));
    client.publish(TOPIC_PUB_LIGHT, toString(lightResult));
    client.publish(TOPIC_PUB_LOUD, toString(loudnessResult));
  }
}
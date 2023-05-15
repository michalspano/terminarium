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
Screen screen = CONNECT_SELECT;           // initialise variable storing current screen to connection selection screen
Screen oldScreen;                         // declare variable storing old screen (used for recognising if screen has changed)
bool shouldUpdateOldScreen;               // declare flag if oldScreen should be updated - necessary for some unique draw functions
bool isStartup = true;                    // declare flag that alters connection screen behavior after first startup

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);         // enable the serial monitor
  pinMode(VIBRATION_PIN, INPUT);          // set up vibration sensor (digital)
  tft.begin();                            // start terminal LCD
  tft.setRotation(3);                     // set terminal LCD rotation

  // set buttons as input that interrupts program loop
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_A), goRightScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_C), goLeftScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_B), goDashScreen, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_5S_PRESS), goConnSelectScreen, FALLING);

  client.setServer(SERVER, 1883);         // set up mqtt server   
  client.setCallback(callback);           // set up behavior when new message received from mqtt broker

  drawHeader();                           // draw headder & background for all screens
}


void loop() {

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

  if(intervalPassed()) {                                   // run code block if desired interval (in ms) has elapsed

    // print sensor data to serial monitor
    Serial.printf("Temperature: %.1f°C\n", temp);          // temperature in Celcius
    Serial.printf("Humidity: %d%% RH\n", humi);            // humidity in percentage
    Serial.printf("Vibration: %s\n", vibResult);           // vibration as string state
    Serial.printf("Moisture: %d%%\n", moistureResult);     // moisture in percentage
    Serial.printf("Light: %d%%\n", lightResult);           // light in percentage
    Serial.printf("Loudness: %d%%\n", loudnessResult);     // loudness in percentage

    SEPARATOR;                                             // visual separator for serial monitor

  // ********************************* PUBLISHING **************************************** //

    if(mqttConnected()) {                                  // if connected, publish each sensor data to mqtt broker
      client.publish(TOPIC_PUB_TEMP, toString(temp));
      client.publish(TOPIC_PUB_HUMI, toString(humi));
      client.publish(TOPIC_PUB_VIB, vibResult);
      client.publish(TOPIC_PUB_MOIST, toString(moistureResult));
      client.publish(TOPIC_PUB_LIGHT, toString(lightResult));
      client.publish(TOPIC_PUB_LOUD, toString(loudnessResult));
    }

  // ***************************** DRAWING (LCD screen) ********************************** //

    // draw screen graphics on LCD
    drawScreen(temp, humi, vibSignal, moistureResult, lightResult, loudnessResult, isStartup);    

    oldScreen = screen;                                    // update oldScreen value, used to determine drawing behavior on next interval                         

  // ***************************** CONNECTING (MQTT) ************************************* //

    connect();                                             // call function to connect WiFi and MQTT according to screen state context
  }                                                        // end code block that runs only per desired interval (ms)
    
  maintainConnection();                                    // call function to maintain or recover connection if it was established but lost

  // check if sensor range update ongoing and if time since last update exceeds defined limit (ms)
  if(isUpdating && (millis() - lastUpdateTime > LOOP_INTERVAL)) {    
    screen = DASHBOARD;                                    // if interval has passed since last update, change screen to dashboard
    isUpdating = false;                                    // set flag to indicate updating has finished
  }
}
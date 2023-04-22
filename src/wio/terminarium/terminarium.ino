/***************************************************************************************************
 * Terminarium
 * File: {@code terminarium.ino}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda, 
 *          Konstantinos Rokanas, Jonathan Boman
 * 
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

// declare imports
#include "DHT.h"      // import DHT library
#include "pins.h"     // import pins for sensors
#include "utils.h"    // import utility functions

// initialise temp&humi sensor-struct
DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(SERIAL_BAUD_RATE); // Enable the serial monitor
  pinMode(VIBRATION_PIN, INPUT);  // Set up digital sensors
  dht.begin();                    // Initialize temp&humi sensor
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

  // ***************************** PARSING ********************************************* //

  float temp            = tempHumiVal[0];
  float humi            = tempHumiVal[1];
  String vibResult      = parseVibrationValue(vibSignal);
  int moistureResult    = mapToPercentage(moistureSignal, MOISTURE);
  int lightResult       = mapToPercentage(lightSignal, LIGHT);
  int loudnessResult    = mapToPercentage(loudnessSignal, LOUDNESS);

  // ***************************** PRINTING (serial monitor) ***************************** //

  Serial.printf("Temperature: %.2f°C\n", temp);         // temperature in Celcius
  Serial.printf("Humidity: %.2f%%RH\n", humi);          // humidity in percentage
  Serial.printf("Vibration: %s\n", vibResult.c_str());  // vibration as string state
  Serial.printf("Moisture: %d%%\n", moistureResult);    // moisture in percentage
  Serial.printf("Light level: %d%%\n", lightResult);    // light in percentage
  Serial.printf("Loudness: %d%%\n", loudnessResult);    // loudness in percentage

  SEPARATOR;          // visual separator for serial monitor
  delay(LOOP_DELAY);  // arbitrary delay to make up for the sensors' latency delay
}

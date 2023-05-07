/***************************************************************************************************
 * Terminarium - utilities, macros, subroutines and constants
 * File: {@code utils.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#include "utils.h"                                      // include corresponding header file

//array storing user defined min and max acceptable values for each sensor type 
int userDefinedRanges[5][2] = {                         
  {15,10},                                              // temperature max & min
  {75,25},                                              // humidity max & min
  {75,25},                                              // moisture max & min
  {75,25},                                              // light max & min
  {75,25},                                              // loudness max & min
  };

// ************************* FORMAT OUTPUT ******************************* //

// visual separator for serial monitor
#define SEPARATOR                \
    for (int i = 0; i < 30; i++) \
        Serial.print(SEP_CHAR);  \
    Serial.println()

/* @toString() the below overloaded functions declare variables as static so they don't
 * just return pointers to local variables that are invalid as soon as function returns*/
 
// convert int to sequence of characters for mqtt publish
char* toString (int value) {
  static char strValue[5];
  sprintf(strValue, "%d", value);
  return(strValue);
}

// convert float to sequence of characters for mqtt publish
char* toString (float value) {
  static char strValue[6];
  sprintf(strValue, "%.1f", value);
  return(strValue);
}

// convert const char* to char* for use in draw functions
char* toString (const char* text) {
  static char charValue[5];               
  strcpy(charValue, text);
  char* result = charValue;
  return result;
}

// ************************ PROGRAM INTERVAL ***************************** //

/* Note: The below function IntervalPassed() was adapted from example code "Blind Without Delay" on Arduino.cc
* Link: https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay */


bool intervalPassed() {                                 // function for checking if interval has passed
  static unsigned long timeStamp = millis();            // store currently elapsed time since program start / last interval (in ms) 
  if (millis() - timeStamp >= LOOP_INTERVAL) {          // if currently elapsed time minus last interval timestamp >= desired interval
    timeStamp = millis();                               // update timestamp of elapsed interval
    return true;                                        // return affirmative
  } 
  return false;
}

// ***************************SENSOR SUBROUTINES ***************************** //

/**
 * Signal coming from sensor does not correspond to any real-world measure,
 * therefore we map the data to a range of [1-100] percent, as a way to intuitively gauge relative measure.
 * @param signal - the signal coming from the sensor
 * @return int - the mapped value
 */
int mapToPercentage(int signal) {
    return map(signal, MIN_READING, MAX_READING, 0, 100);
}

/**
 * Parse the raw vibration signal to a human-readable string.
 * @param vibrationSignal - the raw vibration signal
 * @return String - the parsed vibration signal
 */
char* parseVibrationValue(int vibrationSignal) {
    if (vibrationSignal == 0) {
        delay(350);                                     // arbitrary delay to prevent multiple readings
        return "Vibrating";
    }
    return "Not Vibrating";
}

/* Note: the below function readTempHumi() is adapted from the example code by Toan Nguyen and makes use of their DHT-Sensors-Non-Blocking library:
* Link: https://github.com/toannv17/DHT-Sensors-Non-Blocking */

float* readTempHumi() {                                 // read & parse temp&humi readings
  static float temperature;
  static float humidity;
  static float tempHumi[2];
  static unsigned long timeStamp = millis();            // store currently elapsed time since program start / last interval (in ms) 
  if (millis() - timeStamp >= DHT_INTERVAL) {           // data is measured once per defined interval
    if (dht.measure(&temperature, &humidity)) {     
      timeStamp = millis();                             // update timestamp of elapsed interval 
    }
  }
  tempHumi[0] = temperature;
  tempHumi[1] = humidity;
  return (tempHumi);                                    // return parsed temp&humi values in an array
}

// ************************ UPDATE SENSOR RANGES ***************************** //

bool updateSensorRanges(char* topic, char payload[], unsigned int length){

  screen = UPDATE;                                      // set screen state to update screen

  int newSensorRanges[1];

  if (length != 5){return false;}                       // checking that received message is correct length
  if (strncmp(&payload[2], ",", 1) != 0){return false;} // checking that ',' is in the proper space

  for (int i = 0; i < length; i++){                     // checks that message is in following format: "##,##"
    if(!isDigit(payload[i]) && i < 2 && i > 2 ){return false;}
  }

  //parses received payload 
  char* token = strtok(payload, ",");

  while (token != NULL){
    newSensorRanges[0] = atoi(token);
    token = strtok(NULL, ",");
    newSensorRanges[1] = atoi(token);
    token = strtok(NULL, ",");
  }

  //updates the corresponding sensor range depending on topic
  if(strcmp(topic, "/terminarium/app/range/temperature") == 0 ){
    userDefinedRanges[0][0] = newSensorRanges[0];
    userDefinedRanges[0][1] = newSensorRanges[1];
    return true;
  }else if(strcmp(topic, "/terminarium/app/range/humidity") == 0 ){
    userDefinedRanges[1][0] = newSensorRanges[0];
    userDefinedRanges[1][1] = newSensorRanges[1];
    return true;
  }else if(strcmp(topic, "/terminarium/app/range/moisture") == 0 ){
    userDefinedRanges[2][0] = newSensorRanges[0];
    userDefinedRanges[2][1] = newSensorRanges[1];
    return true;
  }else if(strcmp(topic, "/terminarium/app/range/light") == 0 ){
    userDefinedRanges[3][0] = newSensorRanges[0];
    userDefinedRanges[3][1] = newSensorRanges[1];
    return true;
  }else if(strcmp(topic, "/terminarium/app/range/loudness") == 0 ){
    userDefinedRanges[4][0] = newSensorRanges[0];
    userDefinedRanges[4][1] = newSensorRanges[1];
    return true;
  }else{
    Serial.println("Unrecognized topic");
    return false;
  }
}  
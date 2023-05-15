/***************************************************************************************************
 * Terminarium - utilities, macros, subroutines and constants
 * File: {@code utils.cpp} [source file]
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#include "utils.h"                                      // include corresponding header file


// ************************* PROGRAM INTERVAL **************************** //

/** 
 *Note: The below function IntervalPassed() was adapted from example code "Blind Without Delay" on Arduino.cc
 * Link: https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay 
 */
bool intervalPassed() {                                 // function for checking if interval has passed
  static unsigned long timeStamp = millis();            // store currently elapsed time since program start / last interval (in ms) 
  if (millis() - timeStamp >= LOOP_INTERVAL) {          // if currently elapsed time minus last interval timestamp >= desired interval
    timeStamp = millis();                               // update timestamp of elapsed interval
    return true;                                        // return affirmative
  } 
  return false;
}

// ************************ SENSOR SUBROUTINES *************************** //

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
        return "true";
    }
    return "false";
}

/* Note: the below function readTempHumi() is adapted from the example code by Toan Nguyen and makes use of their DHT-Sensors-Non-Blocking library:
 * Link: https://github.com/toannv17/DHT-Sensors-Non-Blocking 
 */
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


// *********************** UPDATE SENSOR RANGES ************************** //

// array storing user defined min and max acceptable values for each sensor type (initialised with a default preset)
int userDefinedRanges[5][2] = {                         
  {21,28},                                              // temperature min & max
  {10,40},                                              // humidity min & max
  {10,85},                                              // moisture min & max
  {20,65},                                              // light min & max
  {0,65},                                               // loudness min & max
  };

/**
 * @updateSensorRanges: updates array of min/max sensor ranges upon receiving new values via mqtt
 * @param topic - mqtt topic of incoming message String, used to identify sensor/value type
 * @param payload - incoming message String as an array of characters, format must be "###,###"
 * @param length - length of payload String
 */
bool updateSensorRanges(char* topic, char payload[], unsigned int length) {
  if(!validateFormat(payload, length)) {                // call function to validate String payload format
    return false;
  }

  int newSensorRanges[2];                               // create an array of integers to store the new ranges
  parsePayload(payload, newSensorRanges);               // call function to parse payload String into int values

  if(!validateRanges(newSensorRanges[0], newSensorRanges[1])) { // check whether int values are valid (0-100)
    return false;
  } 

  // update the corresponding sensor range depending on topic
  if(strcmp(topic, "/terminarium/app/range/temperature") == 0 ) {
    userDefinedRanges[0][0] = newSensorRanges[0];
    userDefinedRanges[0][1] = newSensorRanges[1];
    return true;
  } else if(strcmp(topic, "/terminarium/app/range/humidity") == 0 ) {
    userDefinedRanges[1][0] = newSensorRanges[0];
    userDefinedRanges[1][1] = newSensorRanges[1];
    return true;
  } else if(strcmp(topic, "/terminarium/app/range/moisture") == 0 ) {
    userDefinedRanges[2][0] = newSensorRanges[0];
    userDefinedRanges[2][1] = newSensorRanges[1];
    return true;
  } else if(strcmp(topic, "/terminarium/app/range/light") == 0 ) {
    userDefinedRanges[3][0] = newSensorRanges[0];
    userDefinedRanges[3][1] = newSensorRanges[1];
    return true;
  } else if(strcmp(topic, "/terminarium/app/range/loudness") == 0 ) {
    userDefinedRanges[4][0] = newSensorRanges[0];
    userDefinedRanges[4][1] = newSensorRanges[1];
    return true;
  } else {
    Serial.println("Unrecognized topic");
    return false;
  }
}  

// checks that incoming message is formatted correctly ("###,###")
bool validateFormat(char payload[], unsigned int length) {
  if (length != 7) {                                    // check that received message is correct length of 7
    return false;
  }                       
  if (strncmp(&payload[3], ",", 1) != 0) {              // check that ',' is in the correct position (index 3)
    return false;
  } 
  for (int i = 0; i < length; i++){                     // loop through characters of payload String
    if(!isDigit(payload[i]) && i < 3 && i > 3 ) {       // check that each character in first 3 and last 3 characters is a digit
      return false;}  
  }  
  return true;
}

// function to parse payload String
void parsePayload(char payload[], int newSensorRanges[]) {
  char* token = strtok(payload, ",");                   // use strtok function to break payload String into two parts separated by the comma

  while (token != NULL){                                
    newSensorRanges[0] = atoi(token);                   // convert first part into integer and store in sensor ranges array index 0 (min value)
    token = strtok(NULL, ",");
    newSensorRanges[1] = atoi(token);                   // convert second part into integer and store in sensor ranges array index 1 (max value)
    token = strtok(NULL, ",");
  }
}

// check that neither min nor max ranges fall below 0 or exceed 100
bool validateRanges(int min, int max) {
  if(min < 0 || min > 100 || max < 0 || max > 100) {    // check that min and max values dont fall below 0 or exceed 100
    return false;
  }
  if(min > max) {                                       // check that min value is not greater than max value
    return false;
  }
  return true;
}


// ************************** FORMAT OUTPUT ****************************** //

// visual separator for serial monitor
#define SEPARATOR                \
    for (int i = 0; i < 30; i++) \
        Serial.print(SEP_CHAR);  \
    Serial.println()

/**
 * @toString: the below overloaded functions declare variables as static so they don't
 * return pointers to local variables that are invalid as soon as function returns
 */

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
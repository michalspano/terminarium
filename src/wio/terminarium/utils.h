/***************************************************************************************************
 * Terminarium - utilities, macros, subroutines and constants
 * File: {@code utils.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#ifndef UTILS_H
#define UTILS_H                     // header guard

#include "DHT_Async.h"              // import DHT library
#define DHTTYPE DHT_TYPE_11         // type of DHT sensor (temp&humi)
extern DHT_Async dht;               // include temp&humi sensor struct

#include "screen_control.h"
extern Screen screen;               // include global screen state variable in current scope 

#define SERIAL_BAUD_RATE 9600       // baud rate for serial monitor
#define MAX_READING 1023            // max possible reading (general)
#define MIN_READING 0               // min possible reading (general)
#define LOOP_INTERVAL 1000          // interval (ms) for program printing and drawing data
#define DHT_INTERVAL 500            // interval (ms) 
#define SEP_CHAR "="                // character used for visual separator

extern int userDefinedRanges[5][2]; //array storing user defined min and max acceptable values for each sensor type 

// ************************* FORMAT OUTPUT ******************************* //

// visual separator for serial monitor
#define SEPARATOR                \
    for (int i = 0; i < 30; i++) \
        Serial.print(SEP_CHAR);  \
    Serial.println()

// convert int to sequence of characters for mqtt publish
extern char* toString (int value);

// convert float to sequence of characters for mqtt publish
extern char* toString (float value);

// convert const char* to char* for use in draw functions
extern char* toString (const char* text);


// ************************ PROGRAM INTERVAL ***************************** //

/* Note: The below function IntervalPassed() was adapted from example code "Blind Without Delay" on Arduino.cc
* Link: https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay */


extern bool intervalPassed();

// ***************************SENSOR SUBROUTINES ***************************** //

/**
 * Signal coming from sensor does not correspond to any real-world measure,
 * therefore we map the data to a range of [1-100] percent, as a way to intuitively gauge relative measure.
 * @param signal - the signal coming from the sensor
 * @return int - the mapped value
 */
extern int mapToPercentage(int signal);

/**
 * Parse the raw vibration signal to a human-readable string.
 * @param vibrationSignal - the raw vibration signal
 * @return String - the parsed vibration signal
 */
extern char* parseVibrationValue(int vibrationSignal);

/* Note: the below function readTempHumi() is adapted from the example code by Toan Nguyen and makes use of their DHT-Sensors-Non-Blocking library:
* Link: https://github.com/toannv17/DHT-Sensors-Non-Blocking */

extern float* readTempHumi();
// ************************ UPDATE SENSOR RANGES ***************************** //

extern bool updateSensorRanges(char* topic, char payload[], unsigned int length);

#endif
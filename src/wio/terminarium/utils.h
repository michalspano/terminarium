/***************************************************************************************************
 * Terminarium - utilities, macros, subroutines and constants
 * File: {@code utils.h} [header file]
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


// ************************* PROGRAM INTERVAL **************************** //

// function for checking if interval has passed
extern bool intervalPassed();


// ************************ SENSOR SUBROUTINES *************************** //

// map raw sensor data to a range of [1-100] percent
extern int mapToPercentage(int signal);

// parse raw vibration data into human-readable sensor
extern char* parseVibrationValue(int vibrationSignal);

// read temp&humi data from DHT sensor
extern float* readTempHumi();


// *********************** UPDATE SENSOR RANGES ************************** //

//array storing user defined min and max acceptable values for each sensor type 
extern int userDefinedRanges[5][2]; 

// update array of max/min sensor ranges upon receiving new values via mqtt
extern bool updateSensorRanges(char* topic, char payload[], unsigned int length);

// checks that incoming message is formatted correctly ("###,###")
bool validateFormat(char payload[], unsigned int length);

// function to parse payload String
void parsePayload(char payload[], int newSensorRanges[]);

// check that neither min nor max ranges fall below 0 or exceed 100
bool validateRanges(int min, int max);


// ************************** FORMAT OUTPUT ****************************** //

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

#endif                              // end header guard  
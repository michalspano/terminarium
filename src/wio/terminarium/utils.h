/***************************************************************************************************
 * Terminarium - utilities, macros, subroutines and constants
 * File: {@code utils.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#define DHTTYPE DHT_TYPE_11         // type of DHT sensor (temp&humi)
extern DHT_Async dht;               // include temp&humi sensor struct

#define SERIAL_BAUD_RATE 9600       // baud rate for serial monitor
#define MAX_READING 1023            // max possible reading (general)
#define MIN_READING 0               // min possible reading (general)
#define LOOP_INTERVAL 1000          // interval (ms) for program printing and drawing data
#define DHT_INTERVAL 500            // interval (ms) 
#define SEP_CHAR "="                // character used for visual separator

// visual separator for serial monitor
#define SEPARATOR                \
    for (int i = 0; i < 30; i++) \
        Serial.print(SEP_CHAR);  \
    Serial.println()

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

// ***************************** SUBROUTINES ***************************** //

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
String parseVibrationValue(int vibrationSignal) {
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
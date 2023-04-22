/***************************************************************************************************
 * Terminarium - utilities, macros, subroutines and constants
 * File: {@code pins.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#define DHTTYPE DHT11               // type of DHT sensor (temp&humi)

#define SERIAL_BAUD_RATE 9600       // baud rate for serial monitor
#define MAX_READING 1023            // max possible reading (general)
#define MAX_READING_MOISTURE 876    // max possible reading from moisture sensor
#define MIN_READING 0               // min possible reading (general)
#define LOOP_DELAY 1000             // delay between each loop iteration (1s)
#define SEP_CHAR "="                // character used for visual separator

// visual separator for serial monitor
#define SEPARATOR                \
    for (int i = 0; i < 30; i++) \
        Serial.print(SEP_CHAR);  \
    Serial.println()

/* enum for the sensor type, used in {@code mapToPercentage}
 * Note: can add more types if required for the future implementation.
 */
enum SensorType {
    TEMP_HUMI,
    VIBRATION,
    MOISTURE,
    LIGHT,
    LOUDNESS
};

// ***************************** SUBROUTINES ***************************** //

/**
 * Signal coming from sensor does not correspond to any real-world measure,
 * therefore we map the data to a range of 1-100 percent, as a way to intuitively gauge relative measure.
 * Note: the moisture sensor requires a different mapping, as it has a different range of values. The light and 
 *      loudness sensors have the same range of values, so they can be mapped in the same way.
 * @param signal - the signal coming from the sensor
 * @return int - the mapped value
 */
int mapToPercentage(int signal, SensorType type) {
    switch (type) {
    case MOISTURE:  // the moisture sensor has a different range of values
        return map(signal, MIN_READING, MAX_READING_MOISTURE, 0, 100);
        break;
    default:        // other sensors (as of now, LIGHT and LOUDNESS) have the same range of values
        return map(signal, MIN_READING, MAX_READING, 0, 100);
        break;
    }
}

/**
 * Parse the raw vibration signal to a human-readable string.
 * @param vibrationSignal - the raw vibration signal
 * @return String - the parsed vibration signal
*/
String parseVibrationValue(int vibrationSignal) {
    if (vibrationSignal == 0) {
        delay(350); // arbitrary delay to prevent multiple readings
        return "Vibrating";
    }
    return "Not Vibrating";
}
/***************************************************************************************************
 * Terminarium - utilities, macros, subroutines and constants
 * File: {@code utils.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#define DHTTYPE DHT11               // type of DHT sensor (temp&humi)

#define SERIAL_BAUD_RATE 9600       // baud rate for serial monitor
#define MAX_READING 1023            // max possible reading (general)
#define MIN_READING 0               // min possible reading (general)
#define LOOP_DELAY 1000             // delay between each loop iteration (1s)
#define SEP_CHAR "="                // character used for visual separator

// visual separator for serial monitor
#define SEPARATOR                \
    for (int i = 0; i < 30; i++) \
        Serial.print(SEP_CHAR);  \
    Serial.println()


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
        delay(350); // arbitrary delay to prevent multiple readings
        return "Vibrating";
    }
    return "Not Vibrating";
}
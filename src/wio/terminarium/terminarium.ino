/***************************************************************************************************
 * Terminarium
 * File: {@code Main.ino}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda, 
 *          Konstantinos Rokanas, Jonathan Boman
 * 
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

// import DHT library
#include "DHT.h"

// macros
#define DHT_PIN       D0        // pin for the temp&humi sensor
#define VIBRATION_PIN D2        // pin for the vibration sensor
#define MOISTURE_PIN  A3        // pin for moisture sensor 
#define LIGHT_PIN     A4        // pin for the LIGHT sensor
#define LOUDNESS_PIN  A5        // pin for the loudness sensor

#define DHTTYPE DHT11           // type of DHT sensor (temp&humi)

#define SERIAL_BAUD_RATE      9600
#define MAX_READING           1023  // max possible reading from loudness and light sensor
#define MIN_READING           0     // min possible reading from loudness and light sensor

#define SEPARATOR for (int i = 0; i < 30; i++) Serial.print("="); Serial.println()

// initialise temp&humi sensor-struct
DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  
  // Enable the serial monitor
  Serial.begin(SERIAL_BAUD_RATE);

  // Set up digital sensors
  pinMode(VIBRATION_PIN, INPUT);

  // Initialize temp&humi sensor
  dht.begin();
}

void loop() {
  // Read sensor data
  int vibSignal   = digitalRead(VIBRATION_PIN);

  // Store sensor output to variable
  int lightSignal = analogRead(LIGHT_PIN);

  // Signal coming from sensor does not correspond to any real-world measure of luminosity
  // Therefore we map the data to a range of 1-100 percent, as a way to intuitively gauge relative light levels.
  int lightValue = map(lightSignal, MIN_READING, MAX_READING, 0, 100);

  //store temperature & humidity data in variables
  float temp  = dht.readTemperature();
  int humi    = dht.readHumidity();

  int loudness            = analogRead(LOUDNESS_PIN);                           // Reading sensor value
  float loudnessPercent   = ((float) loudness / (float) MAX_READING) * 100.0;   // Calculating loudness as percentage of highest possible reading

  // Readung from MOISTURE_PIN
  int moistureRaw         = analogRead(MOISTURE_PIN);

  // Parsing analog read into percentage.
  int moisturePercentage  = map(moistureRaw, MIN_READING, MAX_READING, 0, 100);

  // Variable for storing parsed vibration signal output as string
  String vibResult;

  // If sensor detects vibration, store the result in a variable
  if (vibSignal == 0) {
    vibResult = "Vibrating";
    delay(300);
  } else vibResult = "Not Vibrating";

  // display vibration status
  Serial.println("Vibration status: " + vibResult);

  // print temperature in Celcius
  Serial.printf("Temperature: %.2f°C\n", temp);

  // print humidity as percentage
  Serial.printf("Humidity: %d%%\n", humi);

  // print light data to serial monitor
  Serial.printf("Light level: %d%%\n", lightValue);

  // prints loudness percentage to serial monitor
  Serial.printf("Loudness: %.2f%%\n", loudnessPercent);

  // print the moisture value
  Serial.printf("Moisture: %d%%\n", moisturePercentage);

  // visual separator between each loop's iteration
  SEPARATOR;

  // arbitrary delay to make up for the sensors' latency delay
  delay(500);
}

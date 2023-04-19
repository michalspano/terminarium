#define LOUDNESS_PIN 0
#define MAX_READING 1023 //Max possible reading from sensor
void setup() {
  Serial.begin(9600);
}
void loop() {
  int loudness = analogRead(LOUDNESS_PIN); //Reading sensor value

  float loudnessPercent = ((float) loudness / (float) MAX_READING) * 100.0; // Calculating loudness as percentage of highest possible reading

  Serial.printf("Loudness: %.2f°C\n", loudness); //Prints loudness percentage to serial monitor
  delay(200);
}

// Include the light sensor
#define lightSensor A0

// Setup code, runs once:
void setup() {

  // Initialize the light sensor
  pinMode(lightSensor, INPUT);

  // Enable the serial monitor
  Serial.begin(9600);
}

// Main code, runs repeatedly:
void loop() {

  // Store sensor output to variable
  int signal = analogRead(lightSensor);

  // If terminal receives signal, print confirmation message to serial monitor
  if(signal != NULL) {
    Serial.println("Signal received");
  } else {
    Serial.println("No signal");
  }
}

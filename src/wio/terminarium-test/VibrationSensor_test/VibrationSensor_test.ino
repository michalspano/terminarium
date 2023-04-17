// Include the vibration sensor
#define vib D0

// Setup code, runs once:
void setup() {
    pinMode(vib, INPUT);

    // Enable the serial monitor
    Serial.begin(9600);
}

// Main code, runs repeatedly:
void loop() {
  
  // Store sensor output to variable
  int signal = digitalRead(vib);

  // If sensor detects vibration, print confirmation message
  if(signal != NULL) {
    Serial.println("Signal received"); 
  } else {
    Serial.println("No signal"); 
  }

  // Delay so confirmation message is readable
  delay(200);
  
}
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

  // Variable for storing parsed signal output as string
  String result;

  // If sensor detects vibration, print confirmation message
  if(signal == 0) {
    result = "Vibrating";
  } else {
    result = "Not Vibrating";
  }
  
}

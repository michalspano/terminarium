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

  // If sensor detects vibration, store the result in a variable
  if(signal == 0) {
    result = "Vibrating";
    delay(300);
  } else {
    result = "Not Vibrating";
  }

  // Print vibration signal to serial monitor
  Serial.println("Vibration status: " + result);

  // Delay so message is readable
  delay(100);
  
}

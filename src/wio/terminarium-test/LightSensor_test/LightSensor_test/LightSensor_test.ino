// Include the light sensor
#define lightSensor A0

// Setup code, runs once:
void setup() {

  // Initialize the light sensor
  pinMode(lightSensor, INPUT);

  // Enable the serial monitor
  Serial.begin(9600);
}

// Declare variable to store sensor output
int signal;

// Main code, runs repeatedly:
void loop() {

  // Store sensor output to variable
  signal = analogRead(lightSensor);

  // Map sensor values to %
  signal = map(signal,0,1023,0,100);
}


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

  // Signal coming from sensor does not correspond to any real-world measure of luminosity
  // Therefore we map the data to a range of 1-100 percent, as a way to intuitively gauge relative light levels.
  signal = map(signal,0,1023,0,100);
}


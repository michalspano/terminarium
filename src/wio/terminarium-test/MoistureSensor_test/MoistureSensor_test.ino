
void setup() {
  // That will run only once.
  // Serial.begin() initializes communication between the uno and its sensors or other devices
  // 9600 is the baud rate which represents the speed of how much data can be transmitted per second
  // 9600 is basically how many bps (bits per second) the uno can transmit. 
  // 9600 is normally a safe number here. All other devices must be set to the same number
  // otherwise the data might be currupt/fail and that sucks. 
  Serial.begin(9600);  
}

void loop(){
  // Reading from analog pin A0
  int moistureRaw = analogRead(A0);
  
  // Printing moisture read
  Serial.print("Moisture: ");
  Serial.println(moistureRaw);
  
  // delay, new reading will be printed every 5 seconds
  delay(5000);
}
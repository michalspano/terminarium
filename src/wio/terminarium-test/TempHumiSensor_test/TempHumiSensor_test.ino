//#include "DHT.h" // for later

//define temp&hum sensor
#define dht D0  

void setup() {
  pinMode(dht, INPUT);
  Serial.begin(9600);
}

void loop() {
  float input = digitalRead(dht);
  
  if (input != NULL) {
    Serial.println("It works! :)");
  } else {
    Serial.println("Not working! :(");
  }

}

//import DHT library
#include "DHT.h"

//define pin of sensor
#define DHTPIN D0  

//define type of DHT sensor
#define DHTTYPE DHT11

//initialise sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  
  delay(500);
}

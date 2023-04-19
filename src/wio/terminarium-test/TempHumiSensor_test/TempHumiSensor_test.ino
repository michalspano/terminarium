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
  //store temperature & humidity data in variables
  float temp  = dht.readTemperature();
  int humi    = dht.readHumidity();
  
  //print temperature in Celcius
  Serial.printf("Temperature: %.2f°C\n", temp);

  //print humidity as percentage
  Serial.printf("Humidity: %d%%\n", humi);
  
  delay(500);
}

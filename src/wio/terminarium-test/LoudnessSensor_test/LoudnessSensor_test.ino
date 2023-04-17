#define LOUDNESS_PIN 0

void setup() {
  Serial.begin(9600);
}
void loop() {
  int loudness = analogRead(LOUDNESS_PIN);
  if(loudness != NULL){
      Serial.println("Signal received");
  }else{
    Serial.println("No signal");
  }
  delay(200);
}

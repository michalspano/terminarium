#define LOUDNESS_PIN 0

void setup() {
  Serial.begin(9600);
}
void loop() {
  int loudness = analogRead(LOUDNESS_PIN);
  if(loudness != NULL){
      Serial.printf("Signal received, Loudness: %i\n", loudness);
  }else{
    Serial.println("No signal");
  }
  delay(200);
}

#define PHOTORESISTOR_PIN A0

#define RED_PIN 12
#define GREEN_PIN 10

#define LUMINOSITY_THRESHOLD 300
void setup() {
  Serial.begin(9600);
}

void loop() {
  int luminosity = analogRead(PHOTORESISTOR_PIN);

  if (luminosity < LUMINOSITY_THRESHOLD) {
    digitalWrite(RED_PIN, LOW);
  }
  else {
    digitalWrite(RED_PIN, HIGH);
  }
  
  int scaled = 255 - (luminosity / 4);
  analogWrite(GREEN_PIN, scaled);
}

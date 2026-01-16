#define PHOTORESISTOR_PIN A0

#define RED_PIN 12
#define GREEN_PIN 10

#define LUMINOSITY_THRESHOLD 300

/**
 * @brief Sets up serial.
 * 
 */
void setup() {
  Serial.begin(9600);
}

/**
 * @brief Thsi program 
 * 
 */
void loop() {
  int luminosity = analogRead(PHOTORESISTOR_PIN);

  if (luminosity < LUMINOSITY_THRESHOLD) { // powers on Red LED depending on luminosity threshold
    digitalWrite(RED_PIN, LOW);
  }
  else {
    digitalWrite(RED_PIN, HIGH);
  }

  // sets brightness of Green LED depending on how bright the room is
  int scaled = 255 - (luminosity / 4);
  analogWrite(GREEN_PIN, scaled);
}

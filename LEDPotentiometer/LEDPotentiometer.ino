#define POTENTIOMETER_PIN A2
#define LED_PIN 11

/**
 * @brief Set up serial and pin.
 * 
 */
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

/**
 * @brief This program fades LED depending on the reading from the potentimeter.
 * 
 */
void loop() {
  int potentiometer = analogRead(POTENTIOMETER_PIN);
  Serial.println(potentiometer);
  float scaled_potentiometer = potentiometer / 4;
  analogWrite(LED_PIN, scaled_potentiometer);
}

#define BUTTON_PIN 2
#define LED_PIN 11

/**
 * @brief Sets up the serial and the pins.
 * 
 */
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

/**
*
* @brief This method turns on LED if the push button is pressed.
*/
void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(50);
}

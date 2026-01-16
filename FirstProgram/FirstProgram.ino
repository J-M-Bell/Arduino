/**
 * @brief Sets up pin.
 * 
 */
void setup() {
  // Set LED pin to OUTPUT
  pinMode(12, OUTPUT);
}

/**
 * @brief This program blinks an LED by using the delay function and
 * toggling the LED state.
 * 
 */
void loop() {
  // // Toggle the LED blicking on board
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);
  delay(1000);
}

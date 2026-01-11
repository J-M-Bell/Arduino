void setup() {
  // Set LED pin to OUTPUT
  pinMode(12, OUTPUT);
}

void loop() {
  // // Toggle the LED blicking on board
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);
  delay(1000);
}

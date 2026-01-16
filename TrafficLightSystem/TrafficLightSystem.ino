#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

/**
 * @brief Sets up pins.
 * 
 */
void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

/**
 * @brief This program powers on an LED in order from red, green, then yellow.
 * 
 */
void loop() {
  // red 3s
  digitalWrite(RED_PIN, HIGH);
  delay(3000);
  digitalWrite(RED_PIN, LOW);

  // green 3s
  digitalWrite(GREEN_PIN, HIGH);
  delay(3000);
  digitalWrite(GREEN_PIN, LOW);

  // yellow 1s
  digitalWrite(YELLOW_PIN, HIGH);
  delay(1000);
  digitalWrite(YELLOW_PIN, LOW);
}

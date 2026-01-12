#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10
void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void loop() {
  // red 3s
  // green 3s
  // yellow 1s

  digitalWrite(RED_PIN, HIGH);
  delay(3000);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  delay(3000);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, HIGH);
  delay(1000);
  digitalWrite(YELLOW_PIN, LOW);

}

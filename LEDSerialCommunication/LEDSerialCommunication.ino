#define RED_PIN 12

int delayValue = 100;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  pinMode(RED_PIN, OUTPUT);
  pinMode(RED_PIN, LOW);

}

void loop() {
  if (Serial.available() > 0) {
    int numberFromSerial = Serial.parseInt();
    if (numberFromSerial >= 100 && numberFromSerial <= 1000) {
      delayValue = numberFromSerial;
    }
  }
  Serial.println(delayValue);
  digitalWrite(RED_PIN, HIGH);
  delay(delayValue);
  digitalWrite(RED_PIN, LOW);
  delay(delayValue);
}
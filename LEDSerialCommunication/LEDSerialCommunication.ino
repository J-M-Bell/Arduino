#define RED_PIN 12

int blinkDelay = 100;
int LEDState = LOW;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  pinMode(RED_PIN, OUTPUT);
  pinMode(RED_PIN, LOW);

}

void loop() {
  if (Serial.available() > 0) {
    int data = Serial.parseInt();
    if (data >= 100 && data <= 1000) {
      blinkDelay = data;
    }
  }
  if (LEDState == LOW) {
    LEDState = HIGH;
  }
  else {
    LEDState = LOW;
  }
  pinMode(RED_PIN, LEDState);
  delay(blinkDelay);
}
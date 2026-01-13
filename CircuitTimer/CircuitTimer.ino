#define RED_PIN 12

unsigned long timeCounter = millis();
unsigned long timeIntervalSerialInput = 100;
int LEDState = LOW;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  pinMode(RED_PIN, OUTPUT);
  pinMode(RED_PIN, LOW);

}

void loop() {
  unsigned long timeNow = millis();
  
  if (Serial.available() > 0) {
    int data = Serial.parseInt();
    if (data >= 100 && data <= 1000) {
      timeIntervalSerialInput = data;
    }
  }
  if (timeNow - timeCounter > timeIntervalSerialInput) {
    if (LEDState == LOW) {
      LEDState = HIGH;
    }
    else {
      LEDState = LOW;
    }
    digitalWrite(RED_PIN, LEDState);
    timeCounter += timeIntervalSerialInput;
  }
}
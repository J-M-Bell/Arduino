#define BUTTON_PIN 2

#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

int LEDBlinkState = 1;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (LEDBlinkState == 1) {
      // red and green on, yellow off
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, HIGH);
      LEDBlinkState = 2;
    }
    else {
      // red and green off, yellow on
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      LEDBlinkState = 1;
    }
    delay(300);
  }
}
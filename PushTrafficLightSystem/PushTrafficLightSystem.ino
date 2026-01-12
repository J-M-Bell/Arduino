#define BUTTON_PIN 2

#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

#define LED_PIN_COUNT 3

int LEDBlinkState = 1;

byte LEDPins[LED_PIN_COUNT] = {RED_PIN, YELLOW_PIN, GREEN_PIN};

void setup() {
  setLEDPins();
}

void loop() {
  toggleLEDState();
}

void setLEDPins() {
  pinMode(BUTTON_PIN, INPUT);

  for (byte pin : LEDPins) {
    pinMode(pin, OUTPUT);
    pinMode(pin, LOW);
  }
}

void toggleLEDState() {
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


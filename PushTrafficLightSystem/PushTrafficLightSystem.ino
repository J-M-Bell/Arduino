#define BUTTON_PIN 2

#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

// LED state variables
#define LED_PIN_COUNT 3
int LEDBlinkState = 1;
byte LEDPins[LED_PIN_COUNT] = {RED_PIN, YELLOW_PIN, GREEN_PIN};

/**
 * @brief Sets up LEDs
 * 
 */
void setup() {
  setPins();
}

/**
 * @brief This program toggles the LED from on to off.
 * 
 */
void loop() {
  toggleLEDState();
}

/**
 * @brief This method sets up the pins. 
 * 
 */
void setPins() {
  pinMode(BUTTON_PIN, INPUT);

  for (byte pin : LEDPins) {
    pinMode(pin, OUTPUT);
    pinMode(pin, LOW);
  }
}

/**
 * @brief This method toggles between the red and green LEDs and the yellow LED if the button
 * is released.
 * 
 */
void toggleLEDState() {
  if (digitalRead(BUTTON_PIN) == LOW) { // if button is not pressed
    if (LEDBlinkState == 1) { // red and green on, yellow off
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, HIGH);
      LEDBlinkState = 2;
    }
    else { // red and green off, yellow on
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      LEDBlinkState = 1;
    }
    delay(300);
  }
}


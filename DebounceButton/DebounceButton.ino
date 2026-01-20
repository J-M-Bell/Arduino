#define BUTTON_PIN 2

#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

#define OUTPUT_PIN_COUNT 3
#define INPUT_PIN_COUNT 1

// program state variables
int LEDBlinkState = LOW;
int LEDToggleState = 1;
int buttonState = LOW;

// delay variables
unsigned long LEDClock = millis();
int LEDTimeDelay = 1000;
unsigned long clickTimeCounter = millis();
int buttonTimeDelay = 150;

// pin arrays
byte outputPins[OUTPUT_PIN_COUNT] = {RED_PIN, YELLOW_PIN, GREEN_PIN};
byte inputPins[INPUT_PIN_COUNT] = {BUTTON_PIN};

/**
 * @brief Set the LED output pins.
 * 
 */
void setOutputPins() {
  for (byte outputPin : outputPins) {
    pinMode(outputPin, OUTPUT);
    pinMode(outputPin, LOW);
  }
}

/**
 * @brief Set the input pins.
 * 
 */
void setInputPins() {
  for (byte inputPin : inputPins) {
    pinMode(inputPin, INPUT);
  }
}

/**
 * @brief This method blinks the RED LED.
 * 
 */
void blinkLED() {
  if (LEDBlinkState == LOW) {
      LEDBlinkState = HIGH;
    }
    else {
      LEDBlinkState = LOW;
    }
    digitalWrite(RED_PIN, LEDBlinkState);
    LEDClock += LEDTimeDelay;
}

/**
 * @brief This method is for toggle between the green pin and yellow pin
 * being powered on.
 * 
 */
void toggleLEDs() {
  if (buttonState == HIGH) {
    if (LEDToggleState == 1){
      LEDToggleState = 2;
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      
    }
    else {
      LEDToggleState = 1;
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
    }
  }
}

/**
 * @brief Set up serial and pins
 * 
 */
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  setInputPins();
  setOutputPins();
}

/**
 * @brief This program toggles the green and yellow LED when the
 * push button is pressed.
 * 
 */
void loop() {
  unsigned long timeNow = millis();

  // make LED 1 blink every second
  if (timeNow - LEDClock > LEDTimeDelay) {
    blinkLED();
    //Serial.println("in LED loop.");
  }
  
  // pressed: (LOW -> HIGH): toggle LED 2 & 3
  // toggle LEDs: power on 2, power off 3
  if (timeNow - clickTimeCounter > buttonTimeDelay) { // debounce button
    int newButtonState = digitalRead(BUTTON_PIN);
    if (newButtonState != buttonState) {
      clickTimeCounter = timeNow;
      buttonState = newButtonState;
    }
    toggleLEDs();
  }
}
#include <AUnit.h>

#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

#define POTENTIOMETER_PIN A2
#define BUTTON_PIN 2

#define OUTPUT_PIN_COUNT 3
#define INPUT_PIN_COUNT 2


unsigned long timeCounter = millis();
unsigned long timeIntervalSerialInput = 100;

int LEDState = LOW;

byte outputPins[OUTPUT_PIN_COUNT] = {RED_PIN, YELLOW_PIN, GREEN_PIN};
byte inputPins[INPUT_PIN_COUNT] = {POTENTIOMETER_PIN, BUTTON_PIN};

int pwm;

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
 * @brief This method is used to change the brightness of an
 * LED depending on the reading from the potentiometer.
 * 
 */
void toggleLEDBrightness() {
  int potentiometer = analogRead(POTENTIOMETER_PIN);
  pwm = potentiometer / 4;
  analogWrite(YELLOW_PIN, pwm); 
}

/**
 * @brief This method is for turning on the Green LED when
 * the push button is pressed.
 * 
 */
void blinkLEDWithPushButton() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    digitalWrite(GREEN_PIN, HIGH);
  }
  else {
    digitalWrite(GREEN_PIN, LOW);
  }
}

/**
 * @brief This method is for getting input from the user to change
 * the amount of time delay between turning the LED on or off.
 * 
 */
void changeTimeDelayForLED() {
  unsigned long timeNow = millis();
  // get delay time from user if condition is met
  if (Serial.available() > 0) {
    int data = Serial.parseInt();
    if (data >= 100 && data <= 1000) {
      timeIntervalSerialInput = data;
    }
  }
  // add delay time specified by the user
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

using namespace aunit;

/**
 * @brief This test is for testing that the pwm value used
 * for the LED is within the correct range of values for the
 * LED.
 * 
 */
test(pwmTest) {
  assertTrue(pwm <= 255);
}

/**
 * @brief Set up serial and pins.
 * 
 */
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  setInputPins();
  setOutputPins();
}

/**
 * @brief This program is used to test the CircuitTimer2 program.
 * 
 */
void loop() {
  changeTimeDelayForLED();
    aunit::TestRunner::run();
}

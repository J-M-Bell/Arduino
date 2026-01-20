#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

// LED Array variables
#define LED_PIN_COUNT 3
byte LEDPins[LED_PIN_COUNT] = {RED_PIN, YELLOW_PIN, GREEN_PIN};

// LED States variables
#define LED_STATES_COUNT 2
String LEDState = "";
String LEDStates[2] = {"Locked", "Unlocked"};

// LED Timer variables
unsigned long lastTimeBlinked = millis();
unsigned long lastTimeBlinkedForError = millis();
int LEDDelay;
int LEDErrorDelay = 300;

/**
 * @brief Set up LED pins.
 * 
 */
void setLEDs() {
  for (byte LEDPin : LEDPins) {
    pinMode(LEDPin, OUTPUT);
    pinMode(LEDPin, LOW);
  }
}

/**
 * @brief This method blinks the Yellow LED depending on
 * the distance an object is from the ultrasonic sensor.
 * 
 * @param distance - the distance an object is from the sensor.
 */
void blinkYellowByDistance(double distance) {
  digitalWrite(YELLOW_PIN, LOW);
  // get distance from Ultrasonic sensor continously
  double distanceForLED = getUltrasonicDistance("cm");
  // calculate the time delay in proportion to the distance of the object
  LEDDelay = 1600 / distanceForLED;
  unsigned long timeNow = millis();
  if (timeNow - lastTimeBlinked > LEDDelay) {
    digitalWrite(YELLOW_PIN, HIGH);
    lastTimeBlinked += LEDDelay;
  }
  // blink Yellow LED using timer functionality
}

/**
 * @brief This method controls the brightness of the Green
 * LED depending on the luminosity of the room.
 * 
 * @param luminosity - luminosity value read from the photoresistor.
 */
void controlBrightnessByLuminosity(int luminosity) {
  // get luminosity from the photoresistor continously
  int luminosityForLED = getLuminosity();
  // calculate LED brightness in proportion to the luminosity of the room
  double luminosityScaled = luminosityForLED / 4;
  // set brightness of LED according to luminosity
  double brightness = 255 - luminosityScaled;
  analogWrite(YELLOW_PIN, brightness);
}

/**
 * @brief This method locks the LEDs depending on if
 * an object is past the threshold.
 * 
 */
void lockLEDs() {
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  unsigned long timeNow = millis();
  // update LEDState variable to "Locked"
  LEDState = LEDStates[0];
  // blink Red and Yellow LED at a rate of 300 ms
  if (timeNow - lastTimeBlinkedForError > LEDErrorDelay) {
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(RED_PIN, HIGH);
  }
}

/**
 * @brief This method unlocks the LEDs.
 * 
 */
void unlockLEDs() {
  // update LEDState variable to "Unlocked"
  LEDState = LEDStates[1];
  // call 'blinkYellowByDistance' function
  blinkYellowByDistance(); 
}
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
int LEDDelay;

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
  // get distance from Ultrasonic sensor continously

  // calculate the time delay in proportion to the distance of the object

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

  // calculate LED brightness in proportion to the luminosity of the room

  // set brightness of LED according to luminosity
}

/**
 * @brief This method locks the LEDs depending on if
 * an object is past the threshold.
 * 
 */
void lockLEDs() {
  // update LEDState variable to "Locked"

  // blink Red and Yellow LED at a rate of 300 ms
    //set delay variables
    //blink LED
}

/**
 * @brief This method unlocks the LEDs.
 * 
 */
void unlockLEDs() {
  // update LEDState variable to "Unlocked"

  // call 'blinkYellowByDistance' function
}
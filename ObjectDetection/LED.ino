/**
 * @brief This method blinks the Yellow LED depending on
 * the distance an object is from the ultrasonic sensor.
 * 
 */
void blinkYellowByDistance() {
  // get distance after time delay
  double distanceForLED;

  if (timeNow - lastTimeSensorTriggered > sensorDelay) {
    distanceForLED = getUltrasonicDistance();
    lastTimeSensorTriggered = timeNow + sensorDelay;
  }

  // convert distance to cm for correct blink rate
  if (isInches == 1) {
    distanceForLED = (distanceForLED * 148.0) / 58.0;
  }
  // Serial.print("Distance is: ");
  // Serial.println(distanceForLED);
  LEDDelay = 1600 / (400 / distanceForLED); // TODO: look into equation
  // Serial.print("LEDDelay is: ");
  // Serial.println(LEDDelay);

  // blink Yellow LED depending on calculated delay
  if (timeNow - lastTimeBlinked > LEDDelay) {
    if (LEDState == LOW) {
      LEDState = HIGH;
    }
    else {
      LEDState = LOW;
    }
    digitalWrite(RED_PIN, LEDState);
    // Serial.println("Changed LED State");
    lastTimeBlinked = timeNow;
  }
}

/**
 * @brief This method controls the brightness of the Green
 * LED depending on the luminosity of the room.
 * 
 */
void controlBrightnessByLuminosity() {
  int luminosityForLED;

  // get luminosity after a time delay
  if (timeNow - lastTimeLuminosityChecked > luminosityDelay) {
    luminosityForLED = getLuminosity();
    lastTimeLuminosityChecked = timeNow;
  }
  // lastTimeLuminosityChecked += timeNow;

  // set brightness of LED according to luminosity
  double luminosityScaled = luminosityForLED / 4;
  double brightness = 255 - luminosityScaled;
  analogWrite(GREEN_PIN, brightness);
}

/**
 * @brief This method locks the LEDs depending on if
 * an object is past the threshold.
 * 
 */
void lockLEDs() {
  // power off LEDs
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  
  // blink Red and Yellow LED at a rate of 300 ms
  if (timeNow - lastTimeBlinkedForError > LEDErrorDelay) {
    if (LEDState == LOW) {
      LEDState = HIGH;
    }
    else {
      LEDState = LOW;
    }
    digitalWrite(YELLOW_PIN, LEDState);
    digitalWrite(RED_PIN, LEDState);
    lastTimeBlinkedForError = timeNow;
  }
}
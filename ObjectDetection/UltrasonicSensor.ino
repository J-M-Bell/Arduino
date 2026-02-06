/**
 * @brief This method triggers the Ultrasonic sensor by
 * sending a signal to it.
 * 
 */
void triggerUltrasonicSensor() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
}

/**
 * @brief Get the distance an object is from ultrasonic sensor.
 * 
 * @return double - distance of the object
 */
double getUltrasonicDistance() {
  double distance;
  triggerUltrasonicSensor();

  // get duration of pulse
  double pulseDuration = pulseEnd - pulseStart;
  // Serial.print("The pulse duration is: ");
  // Serial.println(pulseDuration);
  

  // calculate distance depending on current measurement
  if (isInches == 0) {
    distance = pulseDuration / 58.0;
  }
  // else if (isInches == 1) {
    
  // }
  else {
    distance = pulseDuration / 148.0;
  }

  // 148.0 in
  // distance = duration * speed
  // 340 m/s --> 0.034 cm/microseconds
  // duration * 0.034
  // Serial.print("IsInches is: ");
  // Serial.println(isInches);
  if (distance > 400.0) {
    distance = previousDistance;
    return distance;
  }
  previousDistance = distance;
  return distance;
}

/**
 * @brief This method locks the bot if an object has
 * gotten too close to the sensor.
 * 
 */
void lockBot() {
  // update LEDState variable to "Locked"
  lockedMode = true;
  // call 'lockLED' function
  lockLEDs();
  // set LCD state
  LCDState = LCDStates[0];
}

/**
 * @brief This interrupt calculates the duration of the pulse
 * to the Ultrasonic sensor.
 * 
 */
void echoPinInterrupt() {
  // get reading from echo pin
  if (digitalRead(ECHO_PIN) == HIGH) {
    pulseStart = micros();
  }
  else {
    pulseEnd = micros();
    newDistanceAvailable = true;
  }
}


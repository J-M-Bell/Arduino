#define ECHO_PIN 3
#define TRIGGER_PIN 4

unsigned long lastTimeSensorTriggered = micros();
int sensorDelay;
volatile unsigned long pulseStart;
volatile unsigned long pulseEnd;

// Ultrasonic sensor distance variable
volatile bool newDistanceAvailable = false;

/**
 * @brief Sets up the Ultrasonic Sensor component.
 * 
 */
void setUpUltrasonicSensor() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                  echoPinInterrupt,
                  CHANGE);
}

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
double getUltrasonicDistance(String measurement) {
  // get duration of pulse
  double pulseDuration = pulseEnd - pulseStart;
  Serial.print("The pulse duration is: ");
  Serial.println(pulseDuration);
  double distance;
  if (measurement == 'cm') {
    distance = pulseDuration / 58.0;
  }
  else if (measurement == 'in') {
    distance = pulseDuration / 148.0;
  }
  else {
    Serial.print("Incorrect measurement");
  }
   // 148.0 in
  // distance = duration * speed
  // 340 m/s --> 0.034 cm/microseconds
  // duration * 0.034
  return distance;
}

/**
 * @brief Gets the distance in centimeters from the sensor.
 * 
 * @return double - distance from the ultrasonic sensor.
 */
double getDistanceinCentimeters() {
  // call and return 'getUltrasonicDistance' function with 'cm' passed in
  double distance = getUltrasonicDistance("cm");
  return distance;
}

/**
 * @brief Gets the distance in inches from the sensor.
 * 
 * @return double - distance from the ultrasonic sensor.
 */
double getDistanceinInches() {
  // call and return 'getUltrasonicDistance' function with 'in' passed in
  double distance = getUltrasonicDistance("in");
  return distance;
}

/**
 * @brief This method locks the bot if an object has
 * gotten too close to the sensor.
 * 
 * @param distance 
 */
void lockBot(double distance) {
  // call 'lockLED' function

  // call 'printErrorMessageScreen' function
}

/**
 * @brief This interrupt calculates the duration of the pulse
 * to the Ultrasonic sensor.
 * 
 */
void echoPinInterrupt() {
  if (digitalRead(ECHO_PIN) == HIGH) {
    pulseStart = micros();
  }
  else {
    pulseEnd = micros();
    newDistanceAvailable = true;
  }
}


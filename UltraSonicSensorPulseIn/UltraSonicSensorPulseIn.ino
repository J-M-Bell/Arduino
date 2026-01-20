#define ECHO_PIN 3
#define TRIGGER_PIN 4

// ultrasonic sensor delay variables
unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long pulseDelay = 100;


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
  // get duration of pulse
  unsigned long pulseStart = millis();
  double duration = pulseIn(ECHO_PIN, HIGH);
  unsigned long pulseEnd = millis();
  double pulseDuration = pulseEnd - pulseStart;
  Serial.print("The pulse duration is: ");
  Serial.println(pulseDuration);
  double distance = pulseDuration / 58.0;
  // distance = duration * speed
  // 340 m/s --> 0.034 cm/microseconds
  // duration * 0.034
  return distance;
}

/**
 * @brief Sets up serial and pins.
 * 
 */
void setup() {
 Serial.begin(115200);
 Serial.setTimeout(10);
 pinMode(ECHO_PIN, INPUT);
 pinMode(TRIGGER_PIN, OUTPUT);
}

/**
 * @brief This program gets the distance of an object after a delay.
 * 
 */
void loop() {
  unsigned long timeNow = millis();
  if (timeNow - lastTimeUltrasonicTrigger > pulseDelay) {
    lastTimeUltrasonicTrigger += pulseDelay;
    triggerUltrasonicSensor();
    Serial.println(getUltrasonicDistance());
  }
}

#define ECHO_PIN 3
#define TRIGGER_PIN 4

#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

#define OUTPUT_PIN_COUNT 3

// pin array
byte outputPins[OUTPUT_PIN_COUNT] = {RED_PIN, YELLOW_PIN, GREEN_PIN};
double previousDistance = 400.0;

/**
 * @brief Set the Output Pins
 * 
 */
void setOutputPins() {
  for (byte outputPin : outputPins) {
    pinMode(outputPin, OUTPUT);
    pinMode(outputPin, LOW);
  }
}

// Ultrasonic sensor time delay variables
unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long pulseDelay = 100;
volatile unsigned long pulseStart;
volatile unsigned long pulseEnd;

// Ultrasonic sensor distance variables
volatile bool newDistanceAvailable = false;
double objectDistance;

/**
 * @brief This method triggers the Ultrasonic sensor by sending
 * a pulse to the trigger pin.
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
 * @brief This method calculates the distance of an object
 * from the Ultrasonic sensor by using the duration of the
 * returning signal.
 * 
 * @return double the distance of the object from the sensor.
 */
double getUltrasonicDistance() {
  double pulseDuration = pulseEnd - pulseStart;
  Serial.print("The pulse duration is: ");
  Serial.println(pulseDuration);
  double distance = pulseDuration / 58.0;
  // distance = duration * speed
  // 340 m/s --> 0.034 cm/microseconds
  // duration * 0.034
  if (distance > 400.0) {
    distance = previousDistance;
    return distance;
  }
  previousDistance = distance;
  return distance;
}

/**
 * @brief This method is for toggle on LEDs depending
 * on the distance an object is from the Ultrasonic
 * sensor.
 * 
 */
void powerOnLEDs() {
  if (objectDistance > 100) { // distance > 100 cm -> power Green LED
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(RED_PIN, LOW);
  }
  else if (objectDistance >= 15 && objectDistance <= 100) { // distance 15-100 cm -> power Yellow LED
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(RED_PIN, LOW);
  }
  else { // distance < 15cm -> power Red LED
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
  }
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

/**
 * @brief Sets up serial, Ultrasonic sensor pins, and interrupt.
 * 
 */
void setup() {
 Serial.begin(115200);
 Serial.setTimeout(10);
 pinMode(ECHO_PIN, INPUT);
 pinMode(TRIGGER_PIN, OUTPUT);
 setOutputPins();
 attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                echoPinInterrupt,
                CHANGE);
}

/**
 * @brief This program powers different LEDs depending on the distance an object
 * is from the Ultrasonic sensor.
 * 
 */
void loop() {
  unsigned long timeNow = millis();
  if (timeNow - lastTimeUltrasonicTrigger > pulseDelay) { // delay object detection for smoother reading
    lastTimeUltrasonicTrigger += pulseDelay;
    triggerUltrasonicSensor();
    if (newDistanceAvailable) { // object has been detected
      newDistanceAvailable = false;
      objectDistance = getUltrasonicDistance();
      Serial.println(objectDistance);
      powerOnLEDs();
    }
    
  }
}

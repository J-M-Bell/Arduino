/**
 * @brief This method is to be ran in the main setup function.
 * 
 */
void mainSetup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  setLEDs();
  setUpRemote();
  setUpLCD();
  setUpPushButton();
  setUpUltrasonicSensor();
  lcd.clear();
  printInitializingScreen();
  delay(1000);
  lcd.clear();
  LCDState = LCDStates[2];
}

/**
 * @brief Set Up Remote component.
 * 
 */
void setUpRemote() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

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
 * @brief Set the Up LCD component.
 * 
 */
void setUpLCD() {
  lcd.begin(16,2);
}

/**
 * @brief Sets up the Push Button component
 * 
 */
void setUpPushButton() {
  pinMode(BUTTON_PIN, INPUT);
}

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
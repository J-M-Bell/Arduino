/**
 * @brief This method is for printing to the LCD screen depending on the
 * LCDState variable.
 * 
 */
void printScreen() {
  switch (LCDState) {
    case 0:
      printErrorMessageScreen();
      break;
    case 1:
      printDefaultSettingsScreen();
      break;
    case 2:
      printDistanceScreen();
      break;
    case 3:
      printLuminosityScreen();
      break;
  }
}

/**
 * @brief This method prints the error message to
 * the LCD screen.
 * 
 */
void printErrorMessageScreen() {
  // print '!!! Obstacle !!!' to first row
  lcd.setCursor(0, 0);
  String text = "!!! Obstacle !!!";
  lcd.print(text);

  // print 'Press to unlock.' to second row
  lcd.setCursor(0, 1);
  text = "Press to unlock.";
  lcd.print(text);
}

/**
 * @brief This method sets the default
 * settings to the LCD screen to cm.
 * 
 */
void printDefaultSettingsScreen() {
  // print 'Press on OFF to' to first row
  lcd.setCursor(0, 0);
  String text = "Press on OFF to";
  lcd.print(text);

  // save 'reset settings.' to a variable 
  lcd.setCursor(0, 1);
  text = "reset settings.";
  lcd.print(text);
}

/**
 * @brief This method print the distance of an object in the
 * path of the Ultrasonic sensor.
 * 
 */
void printDistanceScreen() {
  double distance;
  double distanceInCentimeters;
  
  // get distance after time delay
  if (timeNow - lastTimeSensorTriggered > sensorDelay) {
    distance = getUltrasonicDistance();
    lastTimeSensorTriggered = timeNow + sensorDelay;
  }

  // Construct text for distance screen
  String text = "";
  if (isInches == 1) { // Current measurement: inches
    // print 'Dist: {distance}' to first row  
    text = "Dist: ";
    text += distance;
    text += " in";
    distanceInCentimeters = (distance * 148) / 58;
  }
  else { // Current measurement: centimeters
    // print 'Dist: {distance}' to first row  
    text = "Dist: ";
    text += distance;
    text += " cm";
    distanceInCentimeters = distance;
  }
  lcd.setCursor(0,0);
  for (int i = text.length(); i <= 15; i++) { // make sure string has length of 16
    text += " ";
  }
  lcd.print(text);


  // Serial.println(distanceInCentimeters);

  // Show messages and lock the bot depending on the distance of an object
  if (distanceInCentimeters > 50) {
    // print 'No obstacle.' to second row
    lcd.setCursor(0, 1);
    text = "No obstacle.    ";
    lcd.print(text);
  }
  else if (distanceInCentimeters >= 10 && distanceInCentimeters <= 50) {
    // print 'No obstacle.' to second row
    lcd.setCursor(0, 1);
    text = "!! Warning !!   ";
    lcd.print(text);
  }
  else {
    lockedMode = true;
  }
}

/**
 * @brief This method print the luminosity from the
 * photoresistor to the LCD screen.
 * 
 * @param luminosity 
 */
void printLuminosityScreen() {
  int luminosity;

  // get luminosity after time delay
  if (timeNow - lastTimeLuminosityChecked > luminosityDelay) {
    luminosity = getLuminosity();
    lastTimeLuminosityChecked = timeNow;
  }
  
  // print 'Luminosity: {luminosity}' to first row
  lcd.setCursor(0, 0);
  String text = "Luminosity: ";
  text += luminosity;
  lcd.print(text);
}

/**
 * @brief This method prints the initializing
 * screen to the LCD.
 * 
 */
void printInitializingScreen() {
  lcd.clear();

  // print 'Initializing...' to LCD
  lcd.setCursor(0, 0);
  String text = "Initializing...";
  lcd.print(text);
}
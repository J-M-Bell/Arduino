/**
 * @brief This method switches the state of
 * the LCD screen when the up button is pressed.
 * 
 */
void upButtonPressed() {
  if (LCDState == LCDStates[1]) { // reset default screen -> distance screen
      LCDState = LCDStates[2];
  }
  else if (LCDState == LCDStates[2]) { // distance screen -> luminosity
    LCDState = LCDStates[3];
  }
  else if (LCDState == LCDStates[3]) { // luminosity -> reset default screen
    LCDState = LCDStates[1];
  }
  lcd.clear();
}

/**
 * @brief This method switches the state of
 * the LCD screen when the down button is pressed.
 * 
 */
void downButtonPressed() {
   if (LCDState == LCDStates[1]) { // reset default screen -> luminosity
    LCDState = LCDStates[3];
  }
  else if (LCDState == LCDStates[3]) { // luminosity -> distance screen
    LCDState = LCDStates[2];
  }
  else if (LCDState == LCDStates[2]) { // distance screen -> reset default screen
    LCDState = LCDStates[1];
  }
  lcd.clear();
}

/**
 * @brief This method changes the default settings
 * of the LCD screen to read either 'cm' or 
 * 'in' for the distance.
 * 
 */
void changeDefaultSettings() {
  if (isInches == 0) { // change to inches
    isInches = 1;
    EEPROM.write(SETTINGS_MEMORY_ADDRESS, isInches);
  }
  else { // change to centimeters
    isInches = 0;
    EEPROM.write(SETTINGS_MEMORY_ADDRESS, isInches);
  }

  // set screen state to distance screen
  LCDState = LCDStates[2];
  lcd.clear();
  // Serial.println("Writing.");
}

/**
 * @brief This method resets the default settings
 * of the LCD screen to 'cm'.
 * 
 */
void resetDefaultSettings() {
  isInches = 0;
  EEPROM.write(SETTINGS_MEMORY_ADDRESS, isInches);
  LCDState = LCDStates[2];
  lcd.clear();
  // Serial.println("Writing");
}



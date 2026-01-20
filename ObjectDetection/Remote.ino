#include <IRremote.h>

//Remote constants
#define IR_RECEIVE_PIN 5
#define PLAY_BUTTON 0x5
#define UP_BUTTON 0xA
#define DOWN_BUTTON 0x8
#define EQ_BUTTON 0xD
#define OFF_BUTTON 0x0

/**
 * @brief Set Up Remote component.
 * 
 */
void setUpRemote() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

/**
 * @brief This method switches the state of
 * the LCD screen when the up button is pressed.
 * 
 */
void upButtonPressed() {
  if (LCDState == LCDStates[2]) { // reset default screen -> distance screen
    if (isCentimeters) {
      LCDState = LCDStates[3];
      printDistanceInCentimetersScreen(getDistanceinCentimeters());
    }
    else {
      LCDState = LCDStates[4];
      printDistanceInInchesScreen(getDistanceinInches());
    }
  }
  else if (LCDState == LCDStates[3] || LCDState == LCDStates[4]) { // distance screen -> luminosity
    LCDState = LCDStates[5];
    printLuminosityScreen();
  }
  else if (LCDState == LCDStates[5]) { // luminosity -> reset default screen
    LCDState = LCDStates[2];
    printDefaultSettingsScreen();
  }
}

/**
 * @brief This method switches the state of
 * the LCD screen when the down button is pressed.
 * 
 */
void downButtonPressed(String command, bool isCentimeters) {
   if (LCDState == LCDStates[2]) { // reset default screen -> distance screen
    LCDState = LCDStates[5];
    printLuminosityScreen();
  }
  else if (LCDState == LCDStates[3] || LCDState == LCDStates[4]) { // distance screen -> luminosity
    LCDState = LCDStates[2];
    printDefaultSettingsScreen();
  }
  else if (LCDState == LCDStates[5]) { // luminosity -> reset default screen
    if (isCentimeters) {
      LCDState = LCDStates[3];
      printDistanceInCentimetersScreen(getDistanceinCentimeters());
    }
    else {
      LCDState = LCDStates[4];
      printDistanceInInchesScreen(getDistanceinInches());
    }
  }
}

/**
 * @brief This method changes the default settings
 * of the LCD screen to read either 'cm' or 
 * 'in' for the distance.
 * 
 */
void changeDefaultSettings() {
  if (LCDState == LCDStates[3] && isCentimeter == true) { // switch cm -> inches
    LCDState = "Distance Inches";
    isCentimeter = false;
    printDistanceInInchesScreen(getDistanceinInches());
  }
  else if (LCDState == LCDStates[4] && isCentimeter == false) { // switch inches -> cm
    LCDState = "Distance Inches";
    isCentimeter = true;
    printDistanceInCentimetersScreen(getDistanceinCentimeters());
  }
}

/**
 * @brief This method resets the default settings
 * of the LCD screen to 'cm'.
 * 
 */
void resetDefaultSettings() {
  // 1. Get the LCD State
  // 2. Change the LCD State to 'cm'
  LCDState = LCDState[3];
  // 3. call printDistance LCD screen with distance as cm (default)
  printDistanceInCentimetersScreen(getDistanceinCentimeters());
}

/**
 * @brief This is a helper to determine the command HEX
 * value that corresponds to the button pressed.
 * 
 */
void printCommands() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  setUpRemote();
  if (IrReceiver.decode()) {
    unsigned long command = IrReceiver.decodedIRData.command; // get command from remote
    Serial.println(command, HEX); 
    IrReceiver.resume();
  }
}


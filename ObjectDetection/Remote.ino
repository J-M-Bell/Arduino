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
  // declare array of available states 

  // add switch statement
    // depending on current screen switch to next
}

/**
 * @brief This method switches the state of
 * the LCD screen when the down button is pressed.
 * 
 */
void downButtonPressed(String command, bool isCentimeters) {
   // declare array of available states 

  // add switch statement
    // depending on current screen switch to next
}

/**
 * @brief This method changes the default settings
 * of the LCD screen to read either 'cm' or 
 * 'in' for the distance.
 * 
 */
void changeDefaultSettings() {
  // 1. get the current state of LCD screen (either cm or in)
  // 2. switch LCD state using if condition 
  // 3. call getDistance function depending on new state of LCD 
  // 4. call the corresponding printDistanceScreen function 
}

/**
 * @brief This method resets the default settings
 * of the LCD screen to 'cm'.
 * 
 */
void resetDefaultSettings() {
  // 1. Get the LCD State
  // 2. Change the LCD State to 'cm'
  // 3. call printDistance LCD screen with distance as cm (default)
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


#define BUTTON_PIN 2

/**
 * @brief Sets up the Push Button component
 * 
 */
void setUpPushButton() {
  pinMode(BUTTON_PIN, INPUT);
}

/**
 * @brief This method unlocks the bot if the
 * push button is pressed.
 * 
 */
void unlockBot() {
  // call unlockLEDs()
  unlockLEDs();
  // call printDistanceInCentimetersScreen()
  printDistanceInCentimetersScreen();
}
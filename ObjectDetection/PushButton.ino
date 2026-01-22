/**
 * @brief This method unlocks the bot if the
 * push button is pressed.
 * 
 */
void unlockBot() {
  lockedMode = false;
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  LCDState = LCDStates[2];
}
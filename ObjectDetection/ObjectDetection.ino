#include "Definitions.h"
#include "Variables.h"

void setup() {
  // put your setup code here, to run once:
  mainSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  timeNow = millis();

  if (!lockedMode) {
    if (timeNow - clickTimeCounter > buttonTimeDelay) {
      if (IrReceiver.decode()) { // if remote button pressed
        unsigned long command = IrReceiver.decodedIRData.command; // get command from remote
        Serial.println(command, HEX);
        if (command == UP_BUTTON) {
          upButtonPressed();
          // Serial.println("Button pressed.");
        }
        else if (command == DOWN_BUTTON) {
          downButtonPressed();
        }
        else if (command == OFF_STAR_BUTTON && LCDState == 1) {
          resetDefaultSettings();
        }
        else if (command == EQ_OK_BUTTON && LCDState == 2) {
          changeDefaultSettings();
        }
        IrReceiver.resume();
      }
      blinkYellowByDistance();
      clickTimeCounter = timeNow + buttonTimeDelay; 
      Serial.print("The state is: ");
      Serial.println(LCDState);
    }
  }
  else {
    Serial.println("locked mode.");
    lockBot();
    if (timeNow - clickTimeCounter > buttonTimeDelay) {
      if (IrReceiver.decode()) { // if remote button pressed
        unsigned long command = IrReceiver.decodedIRData.command; // get command from remote
        Serial.println(command, HEX);
        if (command == PLAY_RIGHT_BUTTON) {
          unlockBot();
          Serial.println("Unlock pressed.");
        }
        IrReceiver.resume();
      }
      clickTimeCounter = timeNow + buttonTimeDelay;
      if (digitalRead(BUTTON_PIN) == HIGH) {
        unlockBot();
      } 
    }
    Serial.print("The state is: ");
    Serial.println(LCDState);
  }
  printScreen();
  controlBrightnessByLuminosity();

  // if-else block for locked mode (if != locked mode)
  // else lockLEDs, change State to locked (no remote buttons can work but the one to unlock), power on push button, printErrorScreen
    // (inside of) if-else block for warning mode (if != warning mode)
    // else printWarningScreen, no buttons can work
      // switch block or a series of ifs
      // if upButton -> run up button
      // if downButton -> run down button
      // if LCDState is on Distance
        // if EQ Button -> set isInches, call printDistance function

  // functions that need to run outside of this: IrRecevier.decode() (maybe), blinkYellowByDistance (except in Locked)
}

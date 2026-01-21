void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  // if-else block for locked mode (if != locked mode)
  // else lockLEDs, change State to locked (no remote buttons can work but the one to unlock), power on push button, printErrorScreen
    // (inside of) if-else block for warning mode (if != warning mode)
    // else printWarningScreen, no buttons can work
      // switch block or a series of ifs
      // if upButton -> run up button
      // if downButton -> run down button
      // if LCDState is on Distance
        // if EQ Button -> set isInches, call printDistance function
}

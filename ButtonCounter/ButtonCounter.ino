#define BUTTON_PIN 2

// push button variables
int pushButtonCounter = 0;
volatile bool buttonPressed = false;
volatile unsigned long lastTimeButtonPressed = millis();
int buttonDelay = 200;

/**
 * @brief This interrupt is triggered when a button is pressed
 * to be used for a button counter
 * 
 */
void buttonPressedInterrupt() {
  unsigned long timeNow = millis();
  if (timeNow - lastTimeButtonPressed > buttonDelay) {
    lastTimeButtonPressed = timeNow;
    buttonPressed = true;
  }
}

/**
 * @brief Sets up Serial, interrupts, and a pin.
 * 
 */
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), 
                   buttonPressedInterrupt,
                   RISING);
  pinMode(BUTTON_PIN, INPUT);
}

/**
 * @brief This program counts how many times a button
 * has been pressed.
 * 
 */
void loop() {
  if (buttonPressed) {
    buttonPressed = false;
    pushButtonCounter++;
    Serial.print("The button has been pressed ");
    Serial.print(pushButtonCounter);
    Serial.println(" times.");
  }
}

#define RED_PIN 12

// LED state and delay variables
int blinkDelay = 100;
int LEDState = LOW;

/**
 * @brief Sets up serial and pins.
 * 
 */
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  pinMode(RED_PIN, OUTPUT);
  pinMode(RED_PIN, LOW);

}

/**
 * @brief This program blinks the LED depending on the blink delay
 * value from the user if it is between 100 and 1000.
 * 
 */
void loop() {

  if (Serial.available() > 0) { // gets input from serial
    int data = Serial.parseInt();
    if (data >= 100 && data <= 1000) {
      blinkDelay = data;
    }
  }

  // blinks LED depending on delay input from user
  if (LEDState == LOW) { 
    LEDState = HIGH;
  }
  else {
    LEDState = LOW;
  }
  pinMode(RED_PIN, LEDState);
  delay(blinkDelay);
}
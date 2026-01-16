#define RED_PIN 12

// timer delay variables
unsigned long timeCounter = millis();
unsigned long timeIntervalSerialInput = 100;

int LEDState = LOW; // LED blinking variable

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  pinMode(RED_PIN, OUTPUT);
  pinMode(RED_PIN, LOW);

}

/**
 * @brief This program takes input from the user to determine the
 * rate that the LED will blink.
 * 
 */
void loop() {
  unsigned long timeNow = millis();
  
  
  if (Serial.available() > 0) { // set blink rate depending on the user input
    int data = Serial.parseInt();
    if (data >= 100 && data <= 1000) {
      timeIntervalSerialInput = data;
    }
  }

  if (timeNow - timeCounter > timeIntervalSerialInput) { // blink LED after a delay
    if (LEDState == LOW) {
      LEDState = HIGH;
    }
    else {
      LEDState = LOW;
    }
    digitalWrite(RED_PIN, LEDState);
    timeCounter += timeIntervalSerialInput;
  }
}
#define LED_PIN 11

/**
*
* @brief This sets up serial monitor and pins.
*/
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

/**
* @brief This method write to an Arduino analog pin 
* to fade LED pin.
* 
* @param int pwm: the pulse width modulation value
*/
void writeToAnalogPin(int pwm){
  analogWrite(LED_PIN, pwm);
  delay(5);
}

/**
*
* @brief This method fades LED in and out continuously.
*/
void loop() {
  // Fade LED from on to off using PWM
  for (int i = 0; i <= 255; i++) {
    writeToAnalogPin(i);
  }
  for (int i = 255; i >= 0; i--) {
    writeToAnalogPin(i);
  }
}

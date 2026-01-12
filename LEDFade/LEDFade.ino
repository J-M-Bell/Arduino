#define LED_PIN 11


void setup() {

}

void writeToAnalogPin(int percentage){
  analogWrite(LED_PIN, i);
  delay(5);
}

void loop() {
  // Fade LED from on to off using PWM
  for (int i = 0; i <= 255; i++){
    writeToAnalogPin(i);
  }
  for (int i = 255; i >= 0; i--){
    writeToAnalogPin(i);
  }
}

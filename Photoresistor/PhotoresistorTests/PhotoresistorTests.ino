#include <AUnit.h>

#define PHOTORESISTOR_PIN A0

unsigned long luminosityClock = millis();
int timeDelay = 100;
/**
 * @brief This test is for testing that the pwm value used
 * for the LED is within the correct range of values for the
 * LED.
 * 
 */
// test(pwmTest) {
//   assertTrue(pwm <= 255);
// }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long timeNow = millis();

  if (timeNow - luminosityClock > timeDelay) {
    int luminosity = analogRead(PHOTORESISTOR_PIN);
    Serial.print("The luminosity is: ");
    Serial.println(luminosity);
  }
}

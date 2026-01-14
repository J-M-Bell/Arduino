#include <EEPROM.h>

#define GREEN_PIN 10
#define POTENTIOMETER_PIN A2

#define MAX_BRIGHTNESS_ADDRESS 100
#define MAX_BIGHTNESS_DEFAULT 255

//int maxIntensity = 255;
byte maxIntensity;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(GREEN_PIN, LOW);
  maxIntensity = EEPROM.read(MAX_BRIGHTNESS_ADDRESS);
  if (maxIntensity == 0) {
    maxIntensity = MAX_BIGHTNESS_DEFAULT;
  }
  Serial.print("The max intensity is: ");
  Serial.println(maxIntensity);
}

void loop() {
  // get max intensity from serial
  if (Serial.available() > 0) {
    int data = Serial.parseInt();
    if (data >= 1 && data <= 255) {
      maxIntensity = data;
      // save max intensity to EEPROM
      Serial.print("The max intensity is now: ");
      Serial.println(maxIntensity);
      EEPROM.write(MAX_BRIGHTNESS_ADDRESS, maxIntensity);
      int memoryValue = EEPROM.read(MAX_BRIGHTNESS_ADDRESS);
      Serial.print("The value saved is: ");
      Serial.println(memoryValue);
    }
  }

  // LED on Pin 10 - fade in/out from potentiometer
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);
  int scale = 1024 / maxIntensity;
  int intensity = potentiometerValue / scale;
  analogWrite(GREEN_PIN, intensity);
}

#include <EEPROM.h>

#define GREEN_PIN 10
#define POTENTIOMETER_PIN A2

#define MAX_BRIGHTNESS_ADDRESS 100
#define MAX_BIGHTNESS_DEFAULT 255

//int maxIntensity = 255;
byte maxIntensity;

void setMaxIntensity() {
  if (Serial.available() > 0) { // get max intensity from serial
    int data = Serial.parseInt();
    if (data >= 1 && data <= 255) {
      maxIntensity = data;

      // save max intensity to EEPROM
      Serial.print("The max intensity is now: ");
      Serial.println(maxIntensity);
      EEPROM.write(MAX_BRIGHTNESS_ADDRESS, maxIntensity);

      // read value from EEPROM (debugging)
      int memoryValue = EEPROM.read(MAX_BRIGHTNESS_ADDRESS);
      Serial.print("The value saved is: ");
      Serial.println(memoryValue);
    }
  }
}

void fadeLED() {
  // LED on Pin 10 - fade in/out from potentiometer
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);
  int scale = 1024 / maxIntensity;
  int intensity = potentiometerValue / scale;
  analogWrite(GREEN_PIN, intensity);
}
/**
 * @brief Sets up serial, pins, and max brightness from EEPROM.
 * 
 */
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(GREEN_PIN, LOW);

  // get max brightness from EEPROM
  maxIntensity = EEPROM.read(MAX_BRIGHTNESS_ADDRESS);
  if (maxIntensity == 0) {
    maxIntensity = MAX_BIGHTNESS_DEFAULT;
  }
  Serial.print("The max intensity is: ");
  Serial.println(maxIntensity);
}

/**
 * @brief This program uses the values from the potentiometer to control the 
 * brightness of the LED and store the potentiometer value in EEPROM to be read if the
 * Arduino resets.
 * 
 */
void loop() {
  setMaxIntensity();
  fadeLED();  
}

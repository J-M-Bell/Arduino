#include <LiquidCrystal.h>

// LCD constants and object
#define LCD_RS_PIN A5
#define LCD_E_PIN A4
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, 
                LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);


int LCDState = 1;

// Ultrasonic sensor time delay variables
unsigned long lastTimeUltrasonicTrigger = micros();
unsigned long pulseDelay = 60;
volatile unsigned long pulseStart;
volatile unsigned long pulseEnd;

/**
 * @brief Sets up serial and LCD
 * 
 */
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  lcd.begin(16, 2);
}

/**
 * @brief Calculate the distance from ultrasonic sensor. 
 * 
 * @return double - the distance an object is from the sensor.
 */
double getUltrasonicDistance() {
  double pulseDuration = pulseEnd - pulseStart;
  Serial.print("The pulse duration is: ");
  Serial.println(pulseDuration);
  double distance = pulseDuration / 58.0;
  // distance = duration * speed
  // 340 m/s --> 0.034 cm/microseconds
  // duration * 0.034
  return distance;
}

/**
 * @brief This program prints the text from the user to 
 * display on the LCD.
 * 
 */
void loop() {
  // 1. get delay time from user if available
  if (Serial.available() > 0) {
    String text = Serial.readString();
    if (text.length() <= 16) {
      if (LCDState == 1) {
        LCDState = 0;
      }
      else {
        LCDState = 1;
      }
      lcd.setCursor(0, LCDState);
      for (int i = text.length(); i >= 16; i++) {
        text += " ";
      }
      lcd.print(text);
    }
  }
}

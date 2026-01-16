#include <LiquidCrystal.h>

// LCD variables
#define LCD_RS_PIN A5
#define LCD_E_PIN A4
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, 
                LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

// Ultrasonic Sensor constants
#define ECHO_PIN 3
#define TRIGGER_PIN 4

// Ultrasonic sensor time delay variables
unsigned long lastTimeUltrasonicTrigger = micros();
unsigned long pulseDelay = 60;
volatile unsigned long pulseStart;
volatile unsigned long pulseEnd;

//
volatile bool newDistanceAvailable = false;
double objectDistance;

/**
 * @brief This method triggers the Ultrasonic sensor by sending
 * a pulse to the trigger pin.
 * 
 */
void triggerUltrasonicSensor() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
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
 * @brief This interrupt calculates the duration of the pulse
 * to the Ultrasonic sensor.
 * 
 */
void echoPinInterrupt() {
  if (digitalRead(ECHO_PIN) == HIGH) {
    pulseStart = micros();
  }
  else {
    pulseEnd = micros();
    newDistanceAvailable = true;
  }
}

/**
 * @brief Sets up serial, LCD, pins, and interrupt.
 * 
 */
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  lcd.begin(16, 2);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                echoPinInterrupt,
                CHANGE);
}

/**
 * @brief This program prints the distance an object is from the Ultrasonic
 * sensor to the LCD screen.
 * 
 */
void loop() {
  unsigned long timeNow = micros();
  if (timeNow - lastTimeUltrasonicTrigger > pulseDelay) { // delay distance reading
    lastTimeUltrasonicTrigger += pulseDelay;
    triggerUltrasonicSensor();
    if (newDistanceAvailable) { // new object detected
      // change distance state and get distance
      newDistanceAvailable = false;
      objectDistance = getUltrasonicDistance();

      // print to LCD
      lcd.setCursor(0, 0);
      lcd.print("rate: ");
      lcd.print(pulseDelay);
      lcd.print(" ms");
      lcd.setCursor(0, 1);
      lcd.print("distance: ");
      lcd.print(objectDistance);
      lcd.print(" cm");
    }
  }
}

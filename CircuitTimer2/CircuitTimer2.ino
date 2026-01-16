#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

#define POTENTIOMETER_PIN A2
#define BUTTON_PIN 2

#define OUTPUT_PIN_COUNT 3
#define INPUT_PIN_COUNT 2


unsigned long timeCounter = millis();
unsigned long timeIntervalSerialInput = 100;

int LEDState = LOW;

byte outputPins[OUTPUT_PIN_COUNT] = {RED_PIN, YELLOW_PIN, GREEN_PIN};
byte inputPins[INPUT_PIN_COUNT] = {POTENTIOMETER_PIN, BUTTON_PIN};

/**
 * @brief Set the LED output pins.
 * 
 */
void setOutputPins() {
  for (byte outputPin : outputPins) {
    pinMode(outputPin, OUTPUT);
    pinMode(outputPin, LOW);
  }
}

/**
 * @brief Set the input pins.
 * 
 */
void setInputPins() {
  for (byte inputPin : inputPins) {
    pinMode(inputPin, INPUT);
  }
}

/**
 * @brief Set up serial and pins.
 * 
 */
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  setInputPins();
  setOutputPins();
}

/**
 * @brief This program is responsible for blinking the Red LED at a rate
 * specified by the user; control the brightness of the Yellow LED with the
 * potentiometer; and power on the Green LED when the push button is pressed.
 * 
 */
void loop() {
  unsigned long timeNow = millis();
  
  // 1. get delay time from user if condition is met
  if (Serial.available() > 0) {
    int data = Serial.parseInt();
    if (data >= 100 && data <= 1000) {
      timeIntervalSerialInput = data;
    }
  }
  // 2. add delay time specified by the user
  if (timeNow - timeCounter > timeIntervalSerialInput) {
    if (LEDState == LOW) {
      LEDState = HIGH;
    }
    else {
      LEDState = LOW;
    }
    digitalWrite(RED_PIN, LEDState);
    timeCounter += timeIntervalSerialInput;
  }

  // 3. set LED 2 (pin 11) brightness with potentiometer
  int potentiometer = analogRead(POTENTIOMETER_PIN);
  int pwm = potentiometer / 4;
  analogWrite(YELLOW_PIN, pwm); 
  

  // 4. power on LED 3 when button is pressed
  if (digitalRead(BUTTON_PIN) == HIGH) {
    digitalWrite(GREEN_PIN, HIGH);
  }
  else {
    digitalWrite(GREEN_PIN, LOW);
  }
}
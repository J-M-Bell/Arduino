#include <IRremote.h>
#include <LiquidCrystal.h>

// IR Remote button constants
#define IR_RECEIVE_PIN 5
#define IR_REMOTE_0 0x19
#define IR_REMOTE_1 0x45
#define IR_REMOTE_2 0x46
#define IR_REMOTE_3 0x47
#define IR_REMOTE_STOP_POUND 0xD

// LCD constants
#define LCD_RS_PIN A5
#define LCD_E_PIN A4
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9

// LED constants
#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

// LED pin state variables
#define OUTPUT_PIN_COUNT 3
byte outputPins[OUTPUT_PIN_COUNT] = {RED_PIN, YELLOW_PIN, GREEN_PIN};
int LEDStates[OUTPUT_PIN_COUNT] = {LOW, LOW, LOW};

// create LCD object
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, 
                LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

unsigned long clickTimeCounter = millis();
int buttonTimeDelay = 150;

/**
 * @brief This method prints text to the LCD screen.
 * 
 * @param text - the text to be displayed on the LCD screen.
 * @param row - the row of the LCD screen for the text to be displayed on.
 */
void printTextForLCDScreen(String text, int row) {
  lcd.setCursor(0, row);
  for (int i = text.length(); i <= 16; i++) {
          text += " ";
  }
  lcd.print(text);
}

/**
 * @brief This method resets the LEDs and the LED states array to default
 * 
 */
void resetOutputPins() {
  for (byte outputPin : outputPins) { // resets pins
    digitalWrite(outputPin, LOW);
  }
  for (int i = 0; i < 3; i++) { // reset states array
    LEDStates[i] = LOW;
  }
}

/**
 * @brief Set the Output Pins.
 * 
 */
void setOutputPins() {
  for (byte outputPin : outputPins) {
    pinMode(outputPin, OUTPUT);
    pinMode(outputPin, LOW);
  }
}

/**
 * @brief This method powers on an LED depending on the index provided.
 * 
 * @param index - the index on the pin to be powered on.
 */
void toggleLEDState(int index) {
  if (LEDStates[index] == LOW) { // turn on LED
    LEDStates[index] = HIGH;
  }
  else if (LEDStates[index] == HIGH) { // turn off LED
    LEDStates[index] = LOW;
  }
  digitalWrite(outputPins[index], LEDStates[index]);
}

/**
 * @brief Set up serial, LCD, and remote.
 * 
 */
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  lcd.begin(16, 2);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

/**
 * @brief This program toggles LEDs and writes to the LCD depending on the 
 * button pressed on the remote.
 * 
 */
void loop() {
  unsigned long timeNow = millis();
  
  if (timeNow - clickTimeCounter > buttonTimeDelay) {
    if (IrReceiver.decode()) { // if remote button pressed
      unsigned long command = IrReceiver.decodedIRData.command; // get command from remote
      Serial.println(command, HEX); 
      // Serial.println(command, HEX);
      // IrReceiver.printIRResultShort(&Serial); 
      // IrReceiver.resume();
      // Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      // Serial.println(IrReceiver.decodedIRData.command);
      // Serial.println("---");
      switch (command) {
        case IR_REMOTE_0: // 0 -> power off all LEDS
          resetOutputPins();
          printTextForLCDScreen("'0' Button", 0);
          printTextForLCDScreen("Power off LEDs", 1);
          break;
        case IR_REMOTE_1: // 1 -> power on Red
          toggleLEDState(0);
          printTextForLCDScreen("'1' Button", 0);
          printTextForLCDScreen("Toggle RED", 1);
          break;
        case IR_REMOTE_2: // 2 -> power on Yellow
          toggleLEDState(1);
          printTextForLCDScreen("'2' Button", 0);
          printTextForLCDScreen("Toggle YELLOW", 1);
          break;
        case IR_REMOTE_3: // 3 -> power on Green
          toggleLEDState(2);
          printTextForLCDScreen("'3' Button", 0);
          printTextForLCDScreen("Toggle GREEN", 1);
          break;
        case IR_REMOTE_STOP_POUND: // FUNC/STOP -> clear LCD
          lcd.clear();
          break;
      }
      IrReceiver.resume();
    }
   clickTimeCounter = timeNow; 
  }
}
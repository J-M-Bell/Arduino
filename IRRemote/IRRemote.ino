#include <IRremote.h>
#include <LiquidCrystal.h>

#define IR_RECEIVE_PIN 5

#define IR_REMOTE_0 0xC
#define IR_REMOTE_1 0x10
#define IR_REMOTE_2 0x11
#define IR_REMOTE_3 0x12
#define IR_REMOTE_STOP 0x2

#define LCD_RS_PIN A5
#define LCD_E_PIN A4
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9

#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

#define OUTPUT_PIN_COUNT 3

byte outputPins[OUTPUT_PIN_COUNT] = {RED_PIN, YELLOW_PIN, GREEN_PIN};

int LEDStates[OUTPUT_PIN_COUNT] = {LOW, LOW, LOW};

LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, 
                LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

int LEDState = LOW;


void printTextForLCDScreen(String text, int row) {
  lcd.setCursor(0, row);
  for (int i = text.length(); i <= 16; i++) {
          text += " ";
  }
  lcd.print(text);
}

void resetOutputPins() {
  for (byte outputPin : outputPins) {
    digitalWrite(outputPin, LOW);
  }
  for (int i = 0; i < 3; i++) {
    LEDStates[i] = LOW;
  }
}

void setOutputPins() {
  for (byte outputPin : outputPins) {
    pinMode(outputPin, OUTPUT);
    pinMode(outputPin, LOW);
  }
}

void toggleLEDState(int index) {
  if (LEDStates[index] == LOW){
    LEDStates[index] = HIGH;
  }
  else if (LEDStates[index] == HIGH) {
    LEDStates[index] = LOW;
  }
  digitalWrite(outputPins[index], LEDStates[index]);
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  lcd.begin(16, 2);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long command = IrReceiver.decodedIRData.command;
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
      case IR_REMOTE_1: // 1 -> power on LED 12
        toggleLEDState(0);
        printTextForLCDScreen("'1' Button", 0);
        printTextForLCDScreen("Toggle RED", 1);
        break;
      case IR_REMOTE_2: // 2 -> power on LED 11
        toggleLEDState(1);
        printTextForLCDScreen("'2' Button", 0);
        printTextForLCDScreen("Toggle YELLOW", 1);
        break;
      case IR_REMOTE_3: // 3 -> power on LED 10
        toggleLEDState(2);
        printTextForLCDScreen("'3' Button", 0);
        printTextForLCDScreen("Toggle GREEN", 1);
        break;
      case IR_REMOTE_STOP: // FUNC/STOP -> clear LCD
        lcd.clear();
        break;
    }
    IrReceiver.resume();
  }
}
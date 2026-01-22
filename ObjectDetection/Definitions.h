// Included files
#include <EEPROM.h>
#include <IRremote.h>
#include <LiquidCrystal.h>

/*          Constants           */

// Distance Measurement Memory Address
#define SETTINGS_MEMORY_ADDRESS 0 

//Remote Constants
#define IR_RECEIVE_PIN 5
#define PLAY_RIGHT_BUTTON 0x5A
#define UP_BUTTON 0x18
#define DOWN_BUTTON 0x52
#define EQ_OK_BUTTON 0x1C
#define OFF_STAR_BUTTON 0x16

//LED Constants
#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10
#define LED_PIN_COUNT 3

// LCD Constants
#define RS_PIN A5
#define E_PIN A4
#define D4_PIN 6
#define D5_PIN 7
#define D6_PIN 8
#define D7_PIN 9
#define LCD_SCREEN_COUNT 4

// Button Constants
#define BUTTON_PIN 2

// Ultrasonic Sensor Constants
#define ECHO_PIN 3
#define TRIGGER_PIN 4

// Photoresistor Constants
#define PHOTORESISTOR_PIN A0



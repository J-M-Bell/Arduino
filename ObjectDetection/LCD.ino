#include <LiquidCrystal.h>

// LCD variables
#define RS_PIN A5
#define E_PIN A4
#define D4_PIN 6
#define D5_PIN 7
#define D6_PIN 8
#define D7_PIN 9
LiquidCrystal lcd(RS_PIN, E_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
#define LCD_SCREEN_COUNT 6

// LCD States variables
String LCDStates[LCD_SCREEN_COUNT] = {"Error", "Warning", "Reset Default", "Distance CM", "Distance Inches", "Luminosity"}; 
String LCDState = "";

bool isCentimeters = true;

/**
 * @brief Set the Up LCD component.
 * 
 */
void setUpLCD() {
  lcd.begin(16,2);
}

/**
 * @brief This method prints the error message to
 * the LCD screen.
 * 
 */
void printErrorMessageScreen() {
  lcd.clear();

  // print '!!! Obstacle !!!' to first row
  lcd.setCursor(0, 1);
  String text = "!!! Obstacle !!!";
  lcd.print(text);

  // print 'Press to unlock.' to second row
  lcd.setCursor(0, 2);
  text = "Press to unlock.";
  lcd.print(text);
}

/**
 * @brief This method sets the default
 * settings to the LCD screen to cm.
 * 
 */
void printDefaultSettingsScreen() {
  lcd.clear();
 
  // print 'Press on OFF to' to first row
  lcd.setCursor(0, 1);
  String text = "Press on OFF to";
  lcd.print(text);

  // save 'reset settings.' to a variable 
  lcd.setCursor(0, 2);
  text = "reset settings.";
  lcd.print(text);
}

/**
 * @brief This method print the distance (in 'cm') of an object in the
 * path of the Ultrasonic sensor.
 * 
 * @param distance - the distance an object is from the sensor.
 */
void printDistanceInCentimetersScreen(double distance) {
  lcd.clear();
 
  // print 'Dist: {distance}' to first row  
  lcd.setCursor(0, 1);
  String text = "Dist: ";
  text += distance;
  text += " cm";
  lcd.print(text);
 
  // print 'No obstacle.' to second row
  lcd.setCursor(0, 2);
  text = "No obstacle.";
  lcd.print(text);
}

/**
 * @brief This method print the distance (in inches) of an object in the
 * path of the Ultrasonic sensor.
 * 
 * @param distance - the distance an object is from the sensor.
 */
void printDistanceInInchesScreen(double distance) {
  lcd.clear();
 
  // print 'Dist: {distance}' to first row  
  lcd.setCursor(0, 1);
  String text = "Dist: ";
  text += distance;
  text += " in";
  lcd.print(text);
 
  // print 'No obstacle.' to second row
  lcd.setCursor(0, 2);
  text = "No obstacle.";
  lcd.print(text);
}

/**
 * @brief This method print the luminosity from the
 * photoresistor to the LCD screen.
 * 
 * @param luminosity 
 */
void printLuminosityScreen(int luminosity) {
  lcd.clear();
 
  // print 'Luminosity: {luminosity}' to first row
  lcd.setCursor(0, 1);
  String text = "Luminosity: ";
  text += luminosity;
  lcd.print(text);
}

/**
 * @brief This method prints the initializing
 * screen to the LCD.
 * 
 */
void printInitializingScreen() {
  lcd.clear();

  // print 'Initializing...' to LCD
  lcd.setCursor(0, 1);
  String text = "Initializing...";
}
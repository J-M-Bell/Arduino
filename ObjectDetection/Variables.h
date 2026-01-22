/*                  Variables                       */

bool lockedMode = false; 

byte isInches = EEPROM.read(SETTINGS_MEMORY_ADDRESS); // state of distance measurement

// main timer for program
unsigned long timeNow;

// Debounce button timer variables
unsigned long clickTimeCounter;
int buttonTimeDelay = 150;

byte LEDPins[LED_PIN_COUNT] = {RED_PIN, YELLOW_PIN, GREEN_PIN};

// LED Timer variables
unsigned long lastTimeBlinked = millis();
unsigned long lastTimeBlinkedForError = millis();
int LEDState = LOW;
int LEDDelay = 1000;
int LEDErrorDelay = 300;

// LCD variables
LiquidCrystal lcd(RS_PIN, E_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN); // initiates LCD
int LCDStates[LCD_SCREEN_COUNT] = {0, 1, 2, 3}; 
int LCDState;

// Luminosity Timer variables
int luminosityDelay = 100;
unsigned long lastTimeLuminosityChecked = millis();

// Ultrasonic Sensor Timer variables
unsigned long lastTimeSensorTriggered = millis();
int sensorDelay = 60;
volatile unsigned long pulseStart;
volatile unsigned long pulseEnd;

// Ultrasonic Sensor distance variable
volatile bool newDistanceAvailable = false;
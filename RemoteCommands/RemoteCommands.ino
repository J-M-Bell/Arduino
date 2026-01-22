#include <IRremote.h>

#define IR_RECEIVE_PIN 5

//REMOTE DEFINITIONS
#define ONE 0x45
#define TWO 0x46
#define THREE 0x47
#define FOUR 0x44
#define FIVE 0x40
#define SIX 0x43
#define SEVEN 0x7
#define EIGHT 0x15
#define NINE 0x9
#define STAR 0x16
#define ZERO 0x19
#define POUND 0xD
#define UP 0x18
#define LEFT 0x8
#define OK 0x1C
#define RIGHT 0x5A
#define DOWN 0x52

unsigned long clickTimeCounter = millis();
int buttonTimeDelay = 150;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(10);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long timeNow = millis();
  
  if (timeNow - clickTimeCounter > buttonTimeDelay) {
    if (IrReceiver.decode()) { // if remote button pressed
      unsigned long command = IrReceiver.decodedIRData.command; // get command from remote
      Serial.println(command, HEX); 
      IrReceiver.printIRResultShort(&Serial); 
      IrReceiver.resume();
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      Serial.println(IrReceiver.decodedIRData.command);
      Serial.println("---");
    }
  }
}

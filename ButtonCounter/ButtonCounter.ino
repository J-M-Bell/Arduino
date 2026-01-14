#define BUTTON_PIN 2

int pushButtonCounter = 0;
volatile int buttonPressed = false;
volatile lastTimeButtonPressed = millis();
int buttonDelay = 50;

void buttonPressedInterrupt() {
  unsigned long timeNow = millis();
  if (timeNow - lastTimeButtonPressed > buttonDelay) {
    buttonPressed = true;
  }
  
}
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), 
                   buttonPressedInterrupt,
                   RISING);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  if (buttonPressed) {
    buttonPressed = false;
    pushButtonCounter++;
    Serial.print("The button has been pressed ");
    Serial.print(pushButtonCounter);
    Serial.println(" times.");
  }
}

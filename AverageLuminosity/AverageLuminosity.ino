#define PHOTORESISTOR_PIN A0

#define LUMINOSITY_COUNT 100

unsigned long lastLuminosityRecordedTime = millis();
int luminosityDelay = 50;

int counter = 0;
int total = 0;
float average;

bool doneRecording = false;

int luminosityValues[LUMINOSITY_COUNT];

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long timeNow = millis();
  if (counter <= 100) {
    if (counter <= 99) {
      if (timeNow - lastLuminosityRecordedTime > luminosityDelay) {
        int luminosity = analogRead(PHOTORESISTOR_PIN);
        Serial.print("Luminosity is: ");
        Serial.println(luminosity);
        luminosityValues[counter] = luminosity;
        Serial.print("The value at index ");
        Serial.print(counter);
        Serial.print(" is: ");
        Serial.println(luminosityValues[counter]);
        total += luminosity;
        Serial.println(total);
        counter++;
      }
      if (counter == 100) {
        average = total / counter;
        Serial.print("The average luminosity is: ");
        Serial.println(average);
      }
    }
  }
}

#define PHOTORESISTOR_PIN A0

#define LUMINOSITY_COUNT 100 // number of luminosity array values

// luminosity time delay variables
unsigned long lastLuminosityRecordedTime = millis();
int luminosityDelay = 50;

// luminosity average calculation variables
int counter = 0;
unsigned long total = 0;
float average;
int luminosityValues[LUMINOSITY_COUNT];

/**
 * @brief Set up serial.
 * 
 */
void setup() {
  Serial.begin(115200);
}

/**
 * @brief This program calculates the average luminosity of an area
 * for a certain amount of time.
 * 
 */
void loop() {
  unsigned long timeNow = millis();
  
  if (counter <= 100) { // create loop to add values to luminosity array
    if (counter <= 99) { //when final array value is reached
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
      if (counter == 100) { // when outside array index range
        average = total / counter;
        Serial.print("The average luminosity is: ");
        Serial.println(average);
      }
    }
  }
}

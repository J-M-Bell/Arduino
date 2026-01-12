#define POTENTIOMETER_PIN A2
#define LED_PIN 11

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int potentiometer = analogRead(POTENTIOMETER_PIN);
  Serial.println(potentiometer);
  float scaled_potentiometer = potentiometer / 4;
  analogWrite(LED_PIN, scaled_potentiometer);
}

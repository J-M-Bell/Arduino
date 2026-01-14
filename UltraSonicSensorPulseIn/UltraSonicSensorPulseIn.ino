#define ECHO_PIN 3
#define TRIGGER_PIN 4

unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long pulseDelay = 100;

void triggerUltrasonicSensor() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
}

double getUltrasonicDistance() {
  unsigned long pulseStart = millis();
  double duration = pulseIn(ECHO_PIN, HIGH);
  unsigned long pulseEnd = millis();
  double pulseDuration = pulseEnd - pulseStart;
  Serial.print("The pulse duration is: ");
  Serial.println(pulseDuration);
  double distance = duration / 58.0;
  // distance = duration * speed
  // 340 m/s --> 0.034 cm/microseconds
  // duration * 0.034
  return distance;
}

void setup() {
 Serial.begin(9600);
 Serial.setTimeout(10);
 pinMode(ECHO_PIN, INPUT);
 pinMode(TRIGGER_PIN, OUTPUT);
}

void loop() {
  unsigned long timeNow = millis();
  if (timeNow - lastTimeUltrasonicTrigger > pulseDelay) {
    lastTimeUltrasonicTrigger += pulseDelay;
    triggerUltrasonicSensor();
    Serial.println(getUltrasonicDistance());
  }
}

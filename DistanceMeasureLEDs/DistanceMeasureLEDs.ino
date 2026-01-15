#define ECHO_PIN 3
#define TRIGGER_PIN 4

#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

#define OUTPUT_PIN_COUNT 3

byte outputPins[OUTPUT_PIN_COUNT] = {RED_PIN, YELLOW_PIN, GREEN_PIN};

void setOutputPins() {
  for (byte outputPin : outputPins) {
    pinMode(outputPin, OUTPUT);
    pinMode(outputPin, LOW);
  }
}

unsigned long lastTimeUltrasonicTrigger = micros();
unsigned long pulseDelay = 60;

volatile unsigned long pulseStart;
volatile unsigned long pulseEnd;

volatile bool newDistanceAvailable = false;

double objectDistance;

void triggerUltrasonicSensor() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
}

double getUltrasonicDistance() {
  double pulseDuration = pulseEnd - pulseStart;
  Serial.print("The pulse duration is: ");
  Serial.println(pulseDuration);
  double distance = pulseDuration / 58.0;
  // distance = duration * speed
  // 340 m/s --> 0.034 cm/microseconds
  // duration * 0.034
  return distance;
}

void echoPinInterrupt() {
  if (digitalRead(ECHO_PIN) == HIGH) {
    pulseStart = micros();
  }
  else {
    pulseEnd = micros();
    newDistanceAvailable = true;
  }
}

void setup() {
 Serial.begin(9600);
 Serial.setTimeout(10);
 pinMode(ECHO_PIN, INPUT);
 pinMode(TRIGGER_PIN, OUTPUT);
 setOutputPins();
 attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                echoPinInterrupt,
                CHANGE);
}

void loop() {
  unsigned long timeNow = micros();
  if (timeNow - lastTimeUltrasonicTrigger > pulseDelay) {
    lastTimeUltrasonicTrigger += pulseDelay;
    triggerUltrasonicSensor();
    if (newDistanceAvailable) {
      newDistanceAvailable = false;
      objectDistance = getUltrasonicDistance();
      Serial.println(objectDistance);
      if (objectDistance > 100) { // distance > 100 cm -> Green LED
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(RED_PIN, LOW);
      }
      else if (objectDistance >= 15 && objectDistance <= 100) { // distance 15-100 cm -> Yellow LED
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(YELLOW_PIN, HIGH);
        digitalWrite(RED_PIN, LOW);
      }
      else { // distance < 15cm -> Red LED
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(YELLOW_PIN, LOW);
        digitalWrite(RED_PIN, HIGH);
      }
    }
    
  }

}

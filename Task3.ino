#include <Servo.h>

const int echoPinSensor1 = 8;
const int trigPinSensor1 = 9;
const int echoPinSensor2 = 6;
const int trigPinSensor2 = 7;
const int echoPinSensor3 = 4;
const int trigPinSensor3 = 5;

Servo baseServo;
int basePosition = 0;

float maxDistance = 35;

void setup() {
  baseServo.attach(3);
  setupInit(echoPinSensor1, trigPinSensor1);
  setupInit(echoPinSensor2, trigPinSensor2);
  setupInit(echoPinSensor3, trigPinSensor3);
  Serial.begin(115200);
}

void setupInit(int echoPin, int trigPin) {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
}

void loop() {
  newPosition();
  baseServo.write(basePosition);
  delay(500);
}

void newPosition() {
  float sensor1 = getPulse(echoPinSensor1, trigPinSensor1);
  float sensor2 = getPulse(echoPinSensor2, trigPinSensor2);
  float sensor3 = getPulse(echoPinSensor3, trigPinSensor3);
  float nearest = min(sensor1, min(sensor2, sensor3));

  const float speedOfSound = 340.0;
  
  float spacing = nearest * speedOfSound / 20000.0;
  if (spacing <= nearest)
  {
      if (nearest == sensor1) {
        basePosition = 0;
      }
      else if (nearest == sensor2) {
        basePosition = 45;
      }
      else {
        basePosition = 90;
    }
  }
}

float getPulse(int echoPin, int trigPin) {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration;
}

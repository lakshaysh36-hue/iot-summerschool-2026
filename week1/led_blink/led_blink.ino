/*
Author: Lakshay Sharma
Date: 02-07-2026
Description:
LED blink program with serial monitoring and potentiometer-controlled blink speed.
*/

const int ledPin = 13;
const int potPin = A0;

int blinkCount = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(potPin);
  int delayTime = map(sensorValue, 0, 1023, 100, 1000);

  digitalWrite(ledPin, HIGH);
  delay(delayTime);

  digitalWrite(ledPin, LOW);
  delay(delayTime);

  blinkCount++;

  Serial.print("Blink count: ");
  Serial.print(blinkCount);
  Serial.print(" | Delay: ");
  Serial.print(delayTime);
  Serial.println(" ms");
}

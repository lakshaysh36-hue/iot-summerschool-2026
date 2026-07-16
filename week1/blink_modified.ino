/*
  Project: LED Blink Pattern

  Description:
  This Arduino program blinks an LED connected to digital pin 13
  three times with a 200 ms interval between ON and OFF states.
  After completing three blinks, it waits for 2 seconds before
  repeating the sequence.

  Author: Lakshay Sharma
  Date: 17 July 2026
*/

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(13, HIGH);
    delay(200);

    digitalWrite(13, LOW);
    delay(200);
  }

  delay(2000);
}

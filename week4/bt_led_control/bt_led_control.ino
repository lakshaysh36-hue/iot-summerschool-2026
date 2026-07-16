
/*
  Project: Bluetooth RGB LED Controller using HC-05

  Description:
  This project uses an Arduino and an HC-05 Bluetooth module to
  control an RGB LED through serial Bluetooth commands. The user
  can turn on the Red, Green, or Blue LED individually, turn all
  LEDs off, or activate a flashing pattern. The Arduino receives
  commands from a paired Bluetooth device and displays the current
  LED status on the Serial Monitor.

  Commands:
  R - Red LED ON
  G - Green LED ON
  B - Blue LED ON
  X - All LEDs OFF
  F - Flash all LEDs 5 times

  Author: Lakshay Sharma
  Date: 17 July 2026
*/
author date description const int RED = 8;
const int GREEN = 9;
const int BLUE = 10;

char command;

void setup() {

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  Serial.begin(9600);      // HC-05 default baud rate

  Serial.println("Bluetooth LED Control Ready");
}

void loop() {

  if (Serial.available()) {

    command = Serial.read();

    switch (command) {

      case 'R':
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, LOW);
        Serial.println("Red LED ON");
        break;

      case 'G':
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, HIGH);
        digitalWrite(BLUE, LOW);
        Serial.println("Green LED ON");
        break;

      case 'B':
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, HIGH);
        Serial.println("Blue LED ON");
        break;

      case 'X':
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, LOW);
        Serial.println("All LEDs OFF");
        break;

      case 'F':

        Serial.println("Flashing LEDs");

        for (int i = 0; i < 5; i++) {

          digitalWrite(RED, HIGH);
          digitalWrite(GREEN, HIGH);
          digitalWrite(BLUE, HIGH);
          delay(300);

          digitalWrite(RED, LOW);
          digitalWrite(GREEN, LOW);
          digitalWrite(BLUE, LOW);
          delay(300);
        }

        break;

      default:
        Serial.println("Invalid Command");
    }
  }
}

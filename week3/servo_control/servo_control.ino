/*
=========================================================
Project : Servo Motor Control using Potentiometer
Author  : Lakshay Sharma

Description:
1. Controls an SG90 servo motor using a potentiometer.
2. Potentiometer value (0-1023) is mapped to
   servo angle (0°-180°).
3. Current servo angle is displayed on the Serial Monitor.
4. A push button performs one complete servo sweep
   (0° -> 180° -> 0°) when pressed.
=========================================================
*/

#include <Servo.h>

//--------------- Pin Definitions -----------------

const int SERVO_PIN = 9;
const int POT_PIN = A0;
const int BUTTON_PIN = 2;

// Create Servo Object
Servo servoMotor;

void setup()
{
  // Attach servo to pin
  servoMotor.attach(SERVO_PIN);

  // Configure button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Start Serial Monitor
  Serial.begin(9600);

  Serial.println("Servo Controller Started");
}

void loop()
{
  // Read potentiometer value
  int potValue = analogRead(POT_PIN);

  // Map 0-1023 to 0-180 degrees
  int angle = map(potValue, 0, 1023, 0, 180);

  // Move servo
  servoMotor.write(angle);

  // Display angle
  Serial.print("Servo Angle: ");
  Serial.print(angle);
  Serial.println(" degrees");

  // Check button press
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    Serial.println("Button Pressed - Servo Sweep Started");

    // Sweep from 0° to 180°
    for (int i = 0; i <= 180; i++)
    {
      servoMotor.write(i);
      delay(10);
    }

    // Sweep back from 180° to 0°
    for (int i = 180; i >= 0; i--)
    {
      servoMotor.write(i);
      delay(10);
    }

    Serial.println("Servo Sweep Completed");
  }

  delay(200);
}

/*Working
Rotate the potentiometer to control the servo angle from 0° to 180°.
The current angle is displayed on the Serial Monitor.
Press the button to make the servo perform one complete sweep:
0° → 180° → 0°
After the sweep, the servo returns to being controlled by the potentiometer.
*?












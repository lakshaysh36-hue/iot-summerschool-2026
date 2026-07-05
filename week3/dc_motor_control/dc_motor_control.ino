/*
=========================================================
Project : DC Motor Control using L298N Driver
Author  : Lakshay Sharma

Description:
This project controls a DC motor using an L298N Motor Driver.

Features:
1. Potentiometer controls motor speed (0-255 PWM).
2. Button 1 changes motor direction
   (Forward <-> Reverse).
3. Button 2 starts/stops the motor.
4. Serial Monitor displays:
   - Direction
   - Speed (%)
   - Motor State
=========================================================
*/

//---------------- Pin Definitions ----------------

// L298N Pins
const int ENA = 9;     // PWM Pin
const int IN1 = 7;
const int IN2 = 8;

// Potentiometer
const int POT_PIN = A0;

// Buttons
const int DIR_BUTTON = 2;
const int START_STOP_BUTTON = 3;

//---------------- Variables ----------------

bool direction = true;      // true = Forward
bool motorRunning = true;

bool lastDirButton = HIGH;
bool lastStartButton = HIGH;

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(DIR_BUTTON, INPUT_PULLUP);
  pinMode(START_STOP_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);

  Serial.println("DC Motor Controller Started");
}

void loop()
{
  // Read potentiometer
  int potValue = analogRead(POT_PIN);

  // Convert to PWM value
  int pwmValue = map(potValue, 0, 1023, 0, 255);

  // Convert to percentage
  int speedPercent = map(potValue, 0, 1023, 0, 100);

  //------------- Direction Button -------------

  bool currentDirButton = digitalRead(DIR_BUTTON);

  if (lastDirButton == HIGH && currentDirButton == LOW)
  {
    direction = !direction;
  }

  lastDirButton = currentDirButton;

  //------------- Start/Stop Button -------------

  bool currentStartButton = digitalRead(START_STOP_BUTTON);

  if (lastStartButton == HIGH && currentStartButton == LOW)
  {
    motorRunning = !motorRunning;
  }

  lastStartButton = currentStartButton;

  //------------- Motor Control -------------

  if (motorRunning)
  {
    analogWrite(ENA, pwmValue);

    if (direction)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    else
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
  }
  else
  {
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }

  //------------- Serial Monitor -------------

  Serial.print("Direction : ");

  if (direction)
    Serial.print("Forward");
  else
    Serial.print("Reverse");

  Serial.print(" | Speed : ");
  Serial.print(speedPercent);
  Serial.print("%");

  Serial.print(" | State : ");

  if (motorRunning)
    Serial.println("Running");
  else
    Serial.println("Stopped");

  delay(200);
}


/*Working
Potentiometer: Controls the motor speed from 0–255 PWM (displayed as 0–100%).
Direction Button (D2): Toggles the motor direction between Forward and Reverse.
Start/Stop Button (D3): Toggles the motor between Running and Stopped.
Serial Monitor: Continuously displays the current direction, speed percentage, and motor state.
*/



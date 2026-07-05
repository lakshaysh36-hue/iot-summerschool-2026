/*
=========================================================
Project : Bluetooth LED Controller
Author  : Lakshay Sharma

Description:
Control three LEDs using an HC-05 Bluetooth module
and an Android Bluetooth Terminal app.

Commands:
R -> Red LED ON
G -> Green LED ON
B -> Blue LED ON
X -> Turn OFF all LEDs
F -> Flash all LEDs 5 times
=========================================================
*/

//--------------- Pin Definitions ----------------

const int RED_LED = 8;
const int GREEN_LED = 9;
const int BLUE_LED = 10;

char command;

void setup()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  Serial.begin(9600);

  Serial.println("Bluetooth LED Controller Ready");
}

void loop()
{
  // Check if data is received via Bluetooth
  if (Serial.available())
  {
    command = Serial.read();

    switch (command)
    {
      // Turn Red LED ON
      case 'R':
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(BLUE_LED, LOW);

        Serial.println("Red LED ON");
        break;

      // Turn Green LED ON
      case 'G':
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(BLUE_LED, LOW);

        Serial.println("Green LED ON");
        break;

      // Turn Blue LED ON
      case 'B':
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(BLUE_LED, HIGH);

        Serial.println("Blue LED ON");
        break;

      // Turn OFF all LEDs
      case 'X':
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(BLUE_LED, LOW);

        Serial.println("All LEDs OFF");
        break;

      // Flash LEDs 5 times
      case 'F':

        Serial.println("Flashing LEDs");

        for (int i = 0; i < 5; i++)
        {
          digitalWrite(RED_LED, HIGH);
          digitalWrite(GREEN_LED, HIGH);
          digitalWrite(BLUE_LED, HIGH);

          delay(300);

          digitalWrite(RED_LED, LOW);
          digitalWrite(GREEN_LED, LOW);
          digitalWrite(BLUE_LED, LOW);

          delay(300);
        }

        Serial.println("Flash Complete");
        break;

      // Invalid command
      default:
        Serial.println("Invalid Command");
        break;
    }
  }
}

/*
Project: Digital Piano
Author: Lakshay Sharma
Description:
Four-note piano with buzzer stop on button release.
*/

const int buzzerPin = 8;

const int doButton = 2;
const int reButton = 3;
const int miButton = 4;
const int faButton = 5;

void setup()
{
    pinMode(doButton, INPUT_PULLUP);
    pinMode(reButton, INPUT_PULLUP);
    pinMode(miButton, INPUT_PULLUP);
    pinMode(faButton, INPUT_PULLUP);

    pinMode(buzzerPin, OUTPUT);
}

void loop()
{
    if (digitalRead(doButton) == LOW)
        tone(buzzerPin, 262);

    else if (digitalRead(reButton) == LOW)
        tone(buzzerPin, 294);

    else if (digitalRead(miButton) == LOW)
        tone(buzzerPin, 330);

    else if (digitalRead(faButton) == LOW)
        tone(buzzerPin, 349);

    else
        noTone(buzzerPin);
}

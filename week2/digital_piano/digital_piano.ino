/*
Project: Digital Piano
Author: Lakshay Sharma
Description:
Four-note piano with Sol chord substitute.
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
    bool doPressed = digitalRead(doButton) == LOW;
    bool rePressed = digitalRead(reButton) == LOW;
    bool miPressed = digitalRead(miButton) == LOW;
    bool faPressed = digitalRead(faButton) == LOW;

    int pressed = doPressed + rePressed + miPressed + faPressed;

    if (pressed >= 2)
    {
        tone(buzzerPin, 392);
    }
    else if (doPressed)
    {
        tone(buzzerPin, 262);
    }
    else if (rePressed)
    {
        tone(buzzerPin, 294);
    }
    else if (miPressed)
    {
        tone(buzzerPin, 330);
    }
    else if (faPressed)
    {
        tone(buzzerPin, 349);
    }
    else
    {
        noTone(buzzerPin);
    }
}






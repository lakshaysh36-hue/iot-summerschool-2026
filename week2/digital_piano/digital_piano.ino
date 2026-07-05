/*
---------------------------------------------------------
Project : Digital Piano using Passive Buzzer
Author  : Lakshay Sharma

Description:
4-key digital piano with:
- Major/Minor mode
- Sol chord substitute
- Button release silence
---------------------------------------------------------
*/

const int buzzerPin = 8;

const int buttonDo = 2;
const int buttonRe = 3;
const int buttonMi = 4;
const int buttonFa = 5;

const int modeButton = 6;

int majorScale[4] = {262, 294, 330, 349};
int minorScale[4] = {262, 294, 311, 349};

bool majorMode = true;
bool lastModeState = HIGH;

void setup()
{
    pinMode(buttonDo, INPUT_PULLUP);
    pinMode(buttonRe, INPUT_PULLUP);
    pinMode(buttonMi, INPUT_PULLUP);
    pinMode(buttonFa, INPUT_PULLUP);

    pinMode(modeButton, INPUT_PULLUP);

    pinMode(buzzerPin, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    bool currentModeState = digitalRead(modeButton);

    if (lastModeState == HIGH && currentModeState == LOW)
    {
        majorMode = !majorMode;
        delay(250);
    }

    lastModeState = currentModeState;

    bool doPressed = digitalRead(buttonDo) == LOW;
    bool rePressed = digitalRead(buttonRe) == LOW;
    bool miPressed = digitalRead(buttonMi) == LOW;
    bool faPressed = digitalRead(buttonFa) == LOW;

    int pressed = doPressed + rePressed + miPressed + faPressed;

    if (pressed >= 2)
    {
        tone(buzzerPin, 392);
    }
    else if (doPressed)
    {
        tone(buzzerPin, majorMode ? majorScale[0] : minorScale[0]);
    }
    else if (rePressed)
    {
        tone(buzzerPin, majorMode ? majorScale[1] : minorScale[1]);
    }
    else if (miPressed)
    {
        tone(buzzerPin, majorMode ? majorScale[2] : minorScale[2]);
    }
    else if (faPressed)
    {
        tone(buzzerPin, majorMode ? majorScale[3] : minorScale[3]);
    }
    else
    {
        noTone(buzzerPin);
    }
}
//connections
//passive buzzer(+)-D8, passive buzzer(-) - GND 
//button1(Do)-D2  button2(Re)-D3  button3(Mi)-D4  Button4(Fa)-D5 mODE BUTTON-D6 other side of every button-GND
//The code uses INPUT_PULLUP, so no external pull-up resistors are required.




















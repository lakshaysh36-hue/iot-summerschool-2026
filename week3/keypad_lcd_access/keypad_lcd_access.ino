/*
=========================================================
Project : Password Protected Access System
Author  : Lakshay Sharma

Description:
1. Displays "ENTER PIN:" on a 16x2 LCD.
2. User enters a 4-digit PIN using a 4x4 keypad.
3. Correct PIN:
   - ACCESS GRANTED
   - Green LED ON
4. Wrong PIN:
   - ACCESS DENIED
   - Red LED ON
   - Buzzer sounds
5. After 3 wrong attempts:
   - System locks for 10 seconds.
=========================================================
*/

#include <Keypad.h>
#include <LiquidCrystal.h>

//---------------- LCD ----------------
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//---------------- Keypad ----------------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {A4, A5, 6, 7};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//---------------- Output Pins ----------------
const int GREEN_LED = 8;
const int RED_LED = 9;
const int BUZZER = 10;

//---------------- Password ----------------
String correctPIN = "1234";
String enteredPIN = "";

int wrongAttempts = 0;

void setup()
{
  lcd.begin(16, 2);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);

  lcd.print("ENTER PIN:");
  lcd.setCursor(0,1);
}

void loop()
{
  // Lock system after 3 wrong attempts
  if (wrongAttempts >= 3)
  {
    lcd.clear();
    lcd.print("SYSTEM LOCKED");

    lcd.setCursor(0,1);
    lcd.print("Wait 10 Sec");

    Serial.println("System Locked");

    delay(10000);

    wrongAttempts = 0;

    lcd.clear();
    lcd.print("ENTER PIN:");
    lcd.setCursor(0,1);

    enteredPIN = "";

    return;
  }

  char key = keypad.getKey();

  if(key)
  {
    Serial.print("Key Pressed: ");
    Serial.println(key);

    lcd.print("*");

    enteredPIN += key;

    // Check after 4 digits
    if(enteredPIN.length() == 4)
    {
      if(enteredPIN == correctPIN)
      {
        lcd.clear();
        lcd.print("ACCESS");
        lcd.setCursor(0,1);
        lcd.print("GRANTED");

        Serial.println("ACCESS GRANTED");

        digitalWrite(GREEN_LED,HIGH);

        delay(3000);

        digitalWrite(GREEN_LED,LOW);

        wrongAttempts = 0;
      }
      else
      {
        lcd.clear();
        lcd.print("ACCESS");
        lcd.setCursor(0,1);
        lcd.print("DENIED");

        Serial.println("ACCESS DENIED");

        digitalWrite(RED_LED,HIGH);

        tone(BUZZER,1000);

        delay(1000);

        noTone(BUZZER);

        digitalWrite(RED_LED,LOW);

        wrongAttempts++;
      }

      enteredPIN="";

      lcd.clear();
      lcd.print("ENTER PIN:");
      lcd.setCursor(0,1);
    }
  }
}

serial output
//Key Pressed: 1
Key Pressed: 2
Key Pressed: 3
Key Pressed: 4
ACCESS GRANTED

Key Pressed: 5
Key Pressed: 5
Key Pressed: 5
Key Pressed: 5
ACCESS DENIED

System Locked






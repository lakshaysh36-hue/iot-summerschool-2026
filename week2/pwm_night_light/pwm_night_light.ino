/*
-------------------------------------------------------------
Project : PWM Fading Night Light
Author  : Lakshay Sharma

Description:
This project creates an automatic night light using PWM.

Modes:
1. Slow Breathing  -> 3-second fade cycle
2. Fast Pulse      -> 0.5-second fade cycle
3. SOS Pattern     -> ... --- ...

A push button changes the mode.

Current mode is displayed on the Serial Monitor.
-------------------------------------------------------------
*/

// ---------------- Pin Definitions ----------------

// PWM pin connected to LED
const int ledPin = 9;

// Push button pin
const int buttonPin = 2;

// Current operating mode
int mode = 1;

// Used to detect button press
bool lastButtonState = HIGH;

void setup()
{
    // Configure LED as OUTPUT
    pinMode(ledPin, OUTPUT);

    // Internal pull-up resistor enabled
    pinMode(buttonPin, INPUT_PULLUP);

    // Start Serial Communication
    Serial.begin(9600);

    Serial.println("PWM Night Light Started");
    Serial.println("Mode 1 : Slow Breathing");
}

void loop()
{
    // Read current button state
    bool currentButtonState = digitalRead(buttonPin);

    // Detect button press
    if (lastButtonState == HIGH && currentButtonState == LOW)
    {
        // Move to next mode
        mode++;

        // After mode 3, return to mode 1
        if (mode > 3)
            mode = 1;

        // Display current mode
        Serial.print("Current Mode : ");

        if (mode == 1)
            Serial.println("Slow Breathing");

        else if (mode == 2)
            Serial.println("Fast Pulse");

        else
            Serial.println("SOS Pattern");

        delay(300);      // Button debounce
    }

    lastButtonState = currentButtonState;

    // Execute selected mode
    if (mode == 1)
    {
        slowBreathing();
    }
    else if (mode == 2)
    {
        fastPulse();
    }
    else
    {
        sosPattern();
    }
}
// MODE 1
// Slow breathing effect
// One complete cycle ≈ 3 seconds

void slowBreathing()
{
    // Fade in
    for (int brightness = 0; brightness <= 255; brightness++)
    {
        analogWrite(ledPin, brightness);
        delay(6);
    }

    // Fade out
    for (int brightness = 255; brightness >= 0; brightness--)
    {
        analogWrite(ledPin, brightness);
        delay(6);
    }
}


// MODE 2
// Fast pulse effect
// One complete cycle ≈ 0.5 second

void fastPulse()
{
    // Fade in quickly
    for (int brightness = 0; brightness <= 255; brightness++)
    {
        analogWrite(ledPin, brightness);
        delay(1);
    }

    // Fade out quickly
    for (int brightness = 255; brightness >= 0; brightness--)
    {
        analogWrite(ledPin, brightness);
        delay(1);
    }
}


// Blink Helper Function

void blinkSignal(int duration)
{
    analogWrite(ledPin, 255);
    delay(duration);

    analogWrite(ledPin, 0);
    delay(200);
}


// MODE 3
// SOS Pattern
// Short = 250 ms
// Long = 750 ms

void sosPattern()
{
    // S = ...
    blinkSignal(250);
    blinkSignal(250);
    blinkSignal(250);

    delay(400);

    // O = ---
    blinkSignal(750);
    blinkSignal(750);
    blinkSignal(750);

    delay(400);

    // S = ...
    blinkSignal(250);
    blinkSignal(250);
    blinkSignal(250);

    delay(1000);
}

/*PWM Night Light Started
Mode 1 : Slow Breathing

Current Mode : Fast Pulse

Current Mode : SOS Pattern

Current Mode : Slow Breathing
*/








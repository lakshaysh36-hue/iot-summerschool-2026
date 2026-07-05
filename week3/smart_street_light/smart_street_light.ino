/*
============================================================
Project : Smart Street Light
Author  : Lakshay Sharma

Description:
This project simulates an intelligent street light
using an LDR and PIR sensor.

Working:
1. During daytime (bright environment)
   - LED remains OFF.

2. During nighttime (dark environment)
   - Motion detection becomes active.

3. Motion detected
   - LED turns ON at full brightness.
   - Remains ON for 30 seconds.

4. No motion after 30 seconds
   - LED dims to 20% brightness using PWM.

5. Every important event is printed to
   the Serial Monitor with a timestamp.

Example:
[00:00:10] EVENT: Motion Detected
============================================================
*/

const int LDR_PIN = A0;
const int PIR_PIN = 2;
const int LED_PIN = 9;        // PWM pin

// LDR threshold
// Lower value = darker
const int LDR_THRESHOLD = 500;

// Time variables
unsigned long motionTime = 0;
bool motionDetected = false;

// Fake clock values for log display
int hh = 0;
int mm = 0;
int ss = 0;


// Prints event with timestamp

void logEvent(String message)
{
    Serial.print("[");

    if(hh < 10) Serial.print("0");
    Serial.print(hh);
    Serial.print(":");

    if(mm < 10) Serial.print("0");
    Serial.print(mm);
    Serial.print(":");

    if(ss < 10) Serial.print("0");
    Serial.print(ss);

    Serial.print("] EVENT: ");
    Serial.println(message);
}


// Updates software clock using millis()

void updateClock()
{
    static unsigned long previousTime = 0;

    if(millis() - previousTime >= 1000)
    {
        previousTime = millis();

        ss++;

        if(ss >= 60)
        {
            ss = 0;
            mm++;
        }

        if(mm >= 60)
        {
            mm = 0;
            hh++;
        }
    }
}

void setup()
{
    pinMode(PIR_PIN, INPUT);

    pinMode(LED_PIN, OUTPUT);

    Serial.begin(9600);

    logEvent("System Started");
}

void loop()
{
    // Update clock every second
    updateClock();

    // Read LDR value
    int lightLevel = analogRead(LDR_PIN);

    // DAY MODE
 
    if(lightLevel > LDR_THRESHOLD)
    {
        // Bright environment
        analogWrite(LED_PIN,0);

        motionDetected = false;

        logEvent("Daylight - LED OFF");

        delay(1000);

        return;
    }

  
    // NIGHT MODE
 

    bool motion = digitalRead(PIR_PIN);

    // Motion detected
    if(motion)
    {
        motionDetected = true;

        motionTime = millis();

        // Full brightness
        analogWrite(LED_PIN,255);

        logEvent("Motion Detected - LED ON");
    }

    // No motion
    if(motionDetected)
    {
        // Keep LED ON for 30 seconds
        if(millis() - motionTime < 30000)
        {
            analogWrite(LED_PIN,255);
        }
        else
        {
            // Dim LED to 20%
            analogWrite(LED_PIN,51);

            motionDetected = false;

            logEvent("No Motion - LED Dimmed");
        }
    }
    else
    {
        // Stay dim at night
        analogWrite(LED_PIN,51);
    }

    delay(100);
}
//ckt connections
/*
Component	Arduino Pin
LDR	A0
PIR Sensor OUT	D2
LED (+)	D9 (PWM)
LED (-)	GND through 220Ω resistor
LDR VCC	5V
LDR GND	GND */
























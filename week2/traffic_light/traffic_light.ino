/*
------------------------------------------------------------
Project: Traffic Light System with Pedestrian Button
Author: Lakshay Sharma
Description:
Simulates a traffic light using three LEDs.
Sequence:
1. RED ON for 5 seconds
2. YELLOW ON for 2 seconds
3. GREEN ON for 4 seconds

If the pedestrian button (Pin 7) is pressed at any time,
the system immediately switches to RED and keeps it ON
for 8 seconds.

The current light state along with the timestamp
(using millis()) is printed on the Serial Monitor.
------------------------------------------------------------
*/

// Pin Definitions
const int RED_LED = 10;
const int YELLOW_LED = 9;
const int GREEN_LED = 8;
const int BUTTON_PIN = 7;

// Function Prototypes
void redLight(unsigned long duration);
void yellowLight(unsigned long duration);
void greenLight(unsigned long duration);
bool pedestrianPressed();

void setup()
{
    // Configure LED pins as outputs
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    // Configure button as input with internal pull-up resistor
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Start Serial Communication
    Serial.begin(9600);
}

// Main Program
void loop()
{
    // Check if pedestrian button is pressed
    if (pedestrianPressed())
    {
        redLight(8000);
        return;
    }

    // Normal Traffic Light Sequence
    redLight(5000);

    if (pedestrianPressed())
    {
        redLight(8000);
        return;
    }

    yellowLight(2000);

    if (pedestrianPressed())
    {
        redLight(8000);
        return;
    }

    greenLight(4000);
}

// Function: Check if pedestrian button is pressed

bool pedestrianPressed()
{
    return digitalRead(BUTTON_PIN) == LOW;
}


// Function: Turn RED LED ON

void redLight(unsigned long duration)
{
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    Serial.print("Time: ");
    Serial.print(millis());
    Serial.println(" ms | RED");

    delay(duration);
}


// Function: Turn YELLOW LED ON

void yellowLight(unsigned long duration)
{
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    Serial.print("Time: ");
    Serial.print(millis());
    Serial.println(" ms | YELLOW");

    delay(duration);
}


// Function: Turn GREEN LED ON

void greenLight(unsigned long duration)
{
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    Serial.print("Time: ");
    Serial.print(millis());
    Serial.println(" ms | GREEN");

    delay(duration);
}








//connections are as follows
//red led-D10
//yellow led-D9
//green led-D8
//push button -D7
//led(-) terminals-GND(through 220 ohm resistors)
other side of push button-GND
//serial monitor output
Time: 0 ms | RED
Time: 5000 ms | YELLOW
Time: 7000 ms | GREEN
Time: 11000 ms | RED


//the button uses INPUT_PULLUP so not pressed-HIGH, pressed-LOW

















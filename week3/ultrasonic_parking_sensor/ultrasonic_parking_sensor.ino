/*
============================================================
Project : Ultrasonic Parking Sensor
Author  : Lakshay Sharma

Description:
This project uses an HC-SR04 ultrasonic sensor to
measure the distance of an object and alerts the user
using LEDs and a buzzer.

Distance Conditions:
------------------------------------------------------------
Distance > 50 cm
    - SAFE
    - No LEDs
    - No buzzer

Distance 20 - 50 cm
    - Yellow LED ON
    - Buzzer beeps every 500 ms

Distance 10 - 20 cm
    - Red LED ON
    - Buzzer beeps every 200 ms

Distance < 10 cm
    - Red & Yellow LEDs flash rapidly
    - Buzzer remains ON continuously

The program uses millis() instead of delay()
to achieve non-blocking timing.
============================================================
*/

// ---------------- Pin Definitions ----------------

const int trigPin = 9;
const int echoPin = 10;

const int yellowLED = 6;
const int redLED = 7;

const int buzzer = 8;

// Variables for millis()
unsigned long previousMillis = 0;

// Stores LED flashing state
bool ledState = false;

void setup()
{
    // Configure ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Configure output devices
    pinMode(yellowLED, OUTPUT);
    pinMode(redLED, OUTPUT);
    pinMode(buzzer, OUTPUT);

    Serial.begin(9600);

    Serial.println("Ultrasonic Parking Sensor Started");
}

void loop()
{
 
    // Generate Trigger Pulse
   

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    
    // Measure Echo Pulse Duration
  

    long duration = pulseIn(echoPin, HIGH);

    // Calculate Distance
-

    float distance = (duration * 0.034) / 2;

    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.println(" cm");

    unsigned long currentMillis = millis();

  
    // SAFE ZONE


    if (distance > 50)
    {
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, LOW);

        noTone(buzzer);

        Serial.println("SAFE");
    }

    // WARNING ZONE


    else if (distance > 20)
    {
        digitalWrite(yellowLED, HIGH);
        digitalWrite(redLED, LOW);

        Serial.println("WARNING");

        // Beep every 500 ms
        if (currentMillis - previousMillis >= 500)
        {
            previousMillis = currentMillis;

            ledState = !ledState;

            if (ledState)
                tone(buzzer, 1000);
            else
                noTone(buzzer);
        }
    }


    // DANGER ZONE


    else if (distance > 10)
    {
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, HIGH);

        Serial.println("DANGER");

        // Beep every 200 ms
        if (currentMillis - previousMillis >= 200)
        {
            previousMillis = currentMillis;

            ledState = !ledState;

            if (ledState)
                tone(buzzer, 1500);
            else
                noTone(buzzer);
        }
    }

   
    // VERY CLOSE
  

    else
    {
        Serial.println("STOP");

        // Continuous buzzer
        tone(buzzer, 2000);

        // Flash LEDs rapidly
        if (currentMillis - previousMillis >= 100)
        {
            previousMillis = currentMillis;

            ledState = !ledState;

            digitalWrite(redLED, ledState);
            digitalWrite(yellowLED, ledState);
        }
    }


//sample serial monitor output
  Distance : 73.6 cm
SAFE

Distance : 38.5 cm
WARNING

Distance : 16.8 cm
DANGER

Distance : 7.2 cm
STOP


  //ckt connections
  */Component	Arduino Pin
HC-SR04 VCC	5V
HC-SR04 GND	GND
HC-SR04 Trig	D9
HC-SR04 Echo	D10
Yellow LED	D6
Red LED	D7
Buzzer	D8 and 220 ohm resistors with leds /*














  
}

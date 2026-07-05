/*
=========================================================
Project : Environmental Monitoring Station
Author  : Lakshay Sharma

Description:
This project uses a DHT11 sensor to monitor
temperature and humidity.

Features:
1. Reads temperature every 2 seconds
2. Displays:
      Timestamp
      Temperature (°C)
      Temperature (°F)
      Humidity (%)
3. Output format:
      timestamp,temp_C,temp_F,humidity
4. Red LED turns ON when:
      Temperature > 35°C
      OR
      Humidity > 80%
5. Green LED turns ON when
   environmental conditions are normal.

Library Used:
Adafruit DHT Sensor Library
=========================================================
*/

#include <DHT.h>

// ---------------- Pin Definitions ----------------

// DHT11 Data Pin
#define DHTPIN 2

// DHT Sensor Type
#define DHTTYPE DHT11

// LED Pins
const int RED_LED = 10;
const int GREEN_LED = 9;

// Create DHT Object
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    // Configure LED Pins
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    // Start Serial Communication
    Serial.begin(9600);

    // Initialize DHT Sensor
    dht.begin();

    Serial.println("timestamp,temp_C,temp_F,humidity");
}

void loop()
{
    // Read Humidity
    float humidity = dht.readHumidity();

    // Read Temperature in Celsius
    float tempC = dht.readTemperature();

    // Read Temperature in Fahrenheit
    float tempF = dht.readTemperature(true);

    // Check if sensor reading failed
    if (isnan(tempC) || isnan(tempF) || isnan(humidity))
    {
        Serial.println("Sensor Read Error");

        delay(2000);
        return;
    }

    // Print data in CSV format
    Serial.print(millis());
    Serial.print(",");

    Serial.print(tempC);
    Serial.print(",");

    Serial.print(tempF);
    Serial.print(",");

    Serial.println(humidity);

    // Check environmental conditions
    if (tempC > 35 || humidity > 80)
    {
        // Dangerous condition

        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
    }
    else
    {
        // Normal condition

        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
    }

    // Read every 2 seconds
    delay(2000);
}

/*
==============================================================
Project : Multi-Sensor Data Logger
Author  : Lakshay Sharma

Description:
Reads data from three sensors simultaneously:

1. DHT11
   - Temperature (°C)
   - Humidity (%)

2. LDR
   - Raw Value (0-1023)
   - Converted to Percentage

3. HC-SR04
   - Distance in centimeters

Outputs formatted sensor data every 5 seconds.

*/

#include <DHT.h>

//---------------- DHT11 ----------------
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

-
const int LDR_PIN = A0;

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Multi Sensor Logger Started");
}

void loop()
{
 
  // Read DHT11


  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();


  // Read LDR


  int ldrRaw = analogRead(LDR_PIN);

  // Convert raw value to percentage
  int lightPercent = map(ldrRaw, 0, 1023, 0, 100);

  String lightStatus;

  if(lightPercent >= 70)
    lightStatus = "Bright";
  else if(lightPercent >= 40)
    lightStatus = "Normal";
  else
    lightStatus = "Dark";

  // Read HC-SR04
  

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = (duration * 0.034) / 2;


  // Display Data
 

  Serial.println("===================");
  Serial.println("=== SENSOR LOG ===");

  Serial.print("Time      : ");
  Serial.print(millis());
  Serial.println(" ms");

  Serial.print("Temp      : ");
  Serial.print(temperature);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.print("Light     : ");
  Serial.print(lightPercent);
  Serial.print("% (");
  Serial.print(lightStatus);
  Serial.println(")");

  Serial.print("Distance  : ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.println("===================");

  // Read every 5 seconds
  delay(5000);
}














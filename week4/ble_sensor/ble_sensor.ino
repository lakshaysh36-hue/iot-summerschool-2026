/*
=========================================================
Project : ESP32 BLE Sensor Dashboard
Author  : Lakshay Sharma

Description:
Broadcast DHT11 sensor data over BLE every 3 seconds.

BLE Characteristics:
1. Temperature
2. Humidity
3. Timestamp

The values can be viewed using:
- nRF Connect
- LightBlue
=========================================================
*/

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <DHT.h>

//--------------- DHT11 ----------------

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//--------------- UUIDs ----------------

// Service UUID
#define SERVICE_UUID        
// Characteristic UUIDs
#define TEMP_UUID          
#define HUM_UUID           
#define TIME_UUID          

BLECharacteristic *tempCharacteristic;
BLECharacteristic *humCharacteristic;
BLECharacteristic *timeCharacteristic;

void setup()
{
  Serial.begin(115200);

  dht.begin();

  // Initialize BLE
  BLEDevice::init("ESP32_DHT11");

  BLEServer *server = BLEDevice::createServer();

  BLEService *service = server->createService(SERVICE_UUID);

  // Temperature Characteristic
  tempCharacteristic = service->createCharacteristic(
      TEMP_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_NOTIFY
  );

  tempCharacteristic->addDescriptor(new BLE2902());

  // Humidity Characteristic
  humCharacteristic = service->createCharacteristic(
      HUM_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_NOTIFY
  );

  humCharacteristic->addDescriptor(new BLE2902());

  // Timestamp Characteristic
  timeCharacteristic = service->createCharacteristic(
      TIME_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_NOTIFY
  );

  timeCharacteristic->addDescriptor(new BLE2902());

  service->start();

  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->start();

  Serial.println("BLE Sensor Started");
}

void loop()
{
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  String timeStamp = String(millis());

  // Skip if sensor read failed
  if (isnan(temp) || isnan(hum))
  {
    Serial.println("Failed to read DHT11");
    delay(3000);
    return;
  }

  // Update BLE Characteristics
  tempCharacteristic->setValue(String(temp).c_str());
  tempCharacteristic->notify();

  humCharacteristic->setValue(String(hum).c_str());
  humCharacteristic->notify();

  timeCharacteristic->setValue(timeStamp.c_str());
  timeCharacteristic->notify();

  // Serial Output
  Serial.print("Temperature : ");
  Serial.print(temp);
  Serial.println(" C");

  Serial.print("Humidity    : ");
  Serial.print(hum);
  Serial.println(" %");

  Serial.print("Timestamp   : ");
  Serial.println(timeStamp);

  Serial.println("--------------------------");

  delay(3000);
}
//ckt connections
DHT11 Pin	ESP32 Pin
VCC	3.3V
GND	GND
DATA	GPIO 4











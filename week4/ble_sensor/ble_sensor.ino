
 /*
  Project: ESP32 BLE Temperature and Humidity Sensor

  Description:
  This project uses an ESP32 and a DHT11 sensor to measure
  temperature and humidity. The ESP32 acts as a Bluetooth Low
  Energy (BLE) server, advertising a custom BLE service with
  three characteristics: temperature, humidity, and timestamp.
  Sensor readings are updated every 3 seconds, sent as BLE
  notifications to connected devices, and displayed on the
  Serial Monitor.

  Author: Lakshay Sharma
  Date: 17 July 2026
*/
author date description #include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLE2901.h>

#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

BLECharacteristic *tempCharacteristic;
BLECharacteristic *humidityCharacteristic;
BLECharacteristic *timeCharacteristic;

unsigned long previousMillis = 0;

#define SERVICE_UUID      "12345678-1234-1234-1234-1234567890AB"
#define TEMP_UUID         "12345678-1234-1234-1234-1234567890AC"
#define HUM_UUID          "12345678-1234-1234-1234-1234567890AD"
#define TIME_UUID         "12345678-1234-1234-1234-1234567890AE"

void setup() {

  Serial.begin(115200);

  dht.begin();

  BLEDevice::init("ESP32 BLE Sensor");

  BLEServer *server = BLEDevice::createServer();

  BLEService *service = server->createService(SERVICE_UUID);

  tempCharacteristic = service->createCharacteristic(
      TEMP_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_NOTIFY
  );

  humidityCharacteristic = service->createCharacteristic(
      HUM_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_NOTIFY
  );

  timeCharacteristic = service->createCharacteristic(
      TIME_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_NOTIFY
  );

  // CCCD
  tempCharacteristic->addDescriptor(new BLE2902());
  humidityCharacteristic->addDescriptor(new BLE2902());
  timeCharacteristic->addDescriptor(new BLE2902());

  // User Description
  BLE2901 *tDesc = new BLE2901();
  tDesc->setDescription("Temperature");
  tempCharacteristic->addDescriptor(tDesc);

  BLE2901 *hDesc = new BLE2901();
  hDesc->setDescription("Humidity");
  humidityCharacteristic->addDescriptor(hDesc);

  BLE2901 *timeDesc = new BLE2901();
  timeDesc->setDescription("Timestamp");
  timeCharacteristic->addDescriptor(timeDesc);

  service->start();

  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->start();

  Serial.println("BLE Started");
}

void loop() {

  if (millis() - previousMillis >= 3000) {

    previousMillis = millis();

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t) && !isnan(h)) {

      String ts = String(millis() / 1000);

      tempCharacteristic->setValue(String(t).c_str());
      humidityCharacteristic->setValue(String(h).c_str());
      timeCharacteristic->setValue(ts.c_str());

      tempCharacteristic->notify();
      humidityCharacteristic->notify();
      timeCharacteristic->notify();

      Serial.print("Temperature: ");
      Serial.println(t);

      Serial.print("Humidity: ");
      Serial.println(h);

      Serial.print("Timestamp: ");
      Serial.println(ts);
    }
  }
}

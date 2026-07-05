# ESP32 BLE Sensor Dashboard

## Description

This project broadcasts DHT11 sensor data over Bluetooth Low Energy (BLE). Any BLE scanner such as **nRF Connect** or **LightBlue** can read the sensor values every 3 seconds.

## BLE Service UUID


12345678-1234-1234-1234-1234567890AB


## Characteristics

### Temperature

UUID


11111111-1111-1111-1111-111111111111


### Humidity

UUID


22222222-2222-2222-2222-222222222222


### Timestamp

UUID


33333333-3333-3333-3333-333333333333


## Update Interval

Every **3 seconds**

## Tested Apps

- nRF Connect
- LightBlue

//we need to install libraries such as esp32 ble arduino,dht sensor library,adrafruit unified sensor
//output
BLE Sensor Started

Temperature : 28.4 C
Humidity    : 65 %
Timestamp   : 3000


Temperature : 28.6 C
Humidity    : 64 %
Timestamp   : 6000

Temperature : 28.8 C
Humidity    : 64 %
Timestamp   : 9000







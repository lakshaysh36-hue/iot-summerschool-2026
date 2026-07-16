# ESP32 MQTT with DHT11

## Objective

Publish DHT11 temperature and humidity data to a public MQTT broker and control an LED remotely.

## Hardware

- ESP32 Dev Module
- DHT11 Sensor
- LED
- 220Ω Resistor
- Breadboard
- Jumper Wires

## MQTT Broker

broker.hivemq.com

## Topics

Temperature:
iitjammu/summer26/lakshay/temperature

Humidity:
iitjammu/summer26/lakshay/humidity

LED Control:
iitjammu/summer26/lakshay/led_control

## JSON Format

Temperature

```json
{"value":31.2,"unit":"C","ts":250000}
```

Humidity

```json
{"value":76.1,"unit":"%","ts":250000}
```

## Features

- Connects ESP32 to Wi-Fi
- Publishes DHT11 readings every 5 seconds
- Sends JSON payload
- Controls LED through MQTT
- Displays status on Serial Monitor

## Screenshots

See the `screenshots` folder.

# ESP32 BLE Sensor

## Components

- ESP32 DevKit
- DHT11 Sensor

## Connections

| DHT11 | ESP32 |
|-------|-------|
| VCC | 3.3V |
| DATA | GPIO4 |
| GND | GND |

## BLE Device Name

ESP32 BLE Sensor

## Service UUID

12345678-1234-1234-1234-1234567890AB

## Characteristics

Temperature

UUID:
12345678-1234-1234-1234-1234567890AC

Humidity

UUID:
12345678-1234-1234-1234-1234567890AD

Timestamp

UUID:
12345678-1234-1234-1234-1234567890AE

## Update Interval

Every 3 seconds

## Testing

1. Upload the sketch to the ESP32.
2. Open nRF Connect or LightBlue on your phone.
3. Scan for "ESP32 BLE Sensor".
4. Connect to the device.
5. Discover the custom service.
6. Read or subscribe (Notify) to the Temperature, Humidity, and Timestamp characteristics.

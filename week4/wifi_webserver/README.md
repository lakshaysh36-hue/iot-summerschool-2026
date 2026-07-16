# ESP32 Wi-Fi Web Server

## Objective
Display DHT11 sensor data on a web page over Wi-Fi.

## Components Used
- ESP32 DevKit
- DHT11 Sensor
- LED
- 220Ω Resistor
- Breadboard
- Jumper Wires

## Connections

### DHT11
- S → GPIO4
- + → 3V3
- - → GND

### LED
- Long leg (+) → GPIO2 (through 220Ω resistor)
- Short leg (-) → GND

## Features
- Displays Temperature
- Displays Humidity
- Displays Uptime
- Auto-refresh every 10 seconds
- Toggle LED button

## Wi-Fi
Replace these values in the code:
- SSID
- Password

## Testing
1. Upload the sketch.
2. Open Serial Monitor (115200 baud).
3. Note the IP address.
4. Open the IP in a browser.
5. Verify temperature, humidity, uptime, and LED control.

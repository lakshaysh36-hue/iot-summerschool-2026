# Project 6: Wi-Fi Weather Dashboard
DRIVE LINK-https://drive.google.com/file/d/1_3uDe-TcyDTDJjWvdOtNRlx7OBlEeILI/view?usp=sharing
## Components Used
//done on both mobile and laptop
* ESP32 Development Board
* DHT11 Temperature and Humidity Sensor
* BMP280 Barometric Pressure Sensor
* LDR Light Sensor Module
* Breadboard
* Jumper Wires
* USB Cable
* Wi-Fi Network

## Wiring Summary

### DHT11 → ESP32

| DHT11 Pin | ESP32  |
| --------- | ------ |
| VCC       | 3.3V   |
| GND       | GND    |
| DATA      | GPIO 4 |

### BMP280 → ESP32 (I2C)

| BMP280 Pin | ESP32   |
| ---------- | ------- |
| VCC        | 3.3V    |
| GND        | GND     |
| SDA        | GPIO 21 |
| SCL        | GPIO 22 |

### LDR Module → ESP32

| LDR Pin | ESP32                             |
| ------- | --------------------------------- |
| VCC     | 3.3V                              |
| GND     | GND                               |
| AO      | Analog input pin used in the code |

> The LDR module's analog output is used to measure the surrounding light level.

## How to Run

1. Connect the DHT11, BMP280, and LDR sensor to the ESP32 according to the wiring summary.
2. Install the required libraries in Arduino IDE:

   * `DHT sensor library`
   * `Adafruit Unified Sensor`
   * `Adafruit BMP280 Library`
3. Enter the correct Wi-Fi network name and password in the code.
4. Connect the ESP32 to the computer using USB.
5. Select:

   * **Board:** ESP32 development board
   * **Port:** Correct ESP32 COM port
6. Upload the code.
7. Open the Serial Monitor at the baud rate specified in the program.
8. Note the IP address printed by the ESP32 after connecting to Wi-Fi.
9. Open that IP address in a web browser connected to the same Wi-Fi network.
10. View the live weather dashboard displaying:

    * Temperature
    * Humidity
    * Atmospheric pressure
    * Approximate altitude
    * Light condition

## Expected Output

### Serial Monitor

After connecting to Wi-Fi, the ESP32 prints sensor readings similar to:

```text id="b6d8d8"
WiFi connected
IP Address: 192.168.x.x

Temperature: 29.70 C
Humidity: 83.60 %
Pressure: 1206.35 hPa
Altitude: 415.59 m
Light: BRIGHT
```

The exact values depend on the environment and sensor readings.

### Web Dashboard

When the IP address is opened in a browser, the dashboard displays updated environmental data.

Example:

```text id="7s6n8h"
Temperature: 29.7 °C
Humidity: 83.6 %
Pressure: 1206.35 hPa
Altitude: 415.59 m
Light: BRIGHT
```

The values update automatically as the sensors detect changes.

### Sensor Behavior

#### Temperature and Humidity

The DHT11 provides:

* Temperature in degrees Celsius
* Relative humidity percentage

#### Atmospheric Pressure

The BMP280 provides:

* Atmospheric pressure in hPa
* Approximate altitude calculated from pressure

#### Light Level

The LDR measures ambient light conditions.

Example:

```text id="2af5qz"
Light: BRIGHT
```

or:

```text id="uk8h2f"
Light: DARK
```

depending on the surrounding light level.

## HTML Page Source Code

The ESP32 generates and serves the dashboard HTML page directly from the microcontroller using the `buildHtmlPage()` function.

The main HTML page structure is:

```html
<!DOCTYPE html>
<html>

<head>
  <meta charset="UTF-8">

  <meta name="viewport"
        content="width=device-width, initial-scale=1">

  <title>ESP32 Wi-Fi Weather Dashboard</title>

  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      margin: 0;
      padding: 20px;
      background: #eaf6ff;
    }

    .container {
      max-width: 900px;
      margin: auto;
    }

    .cards {
      display: grid;
      grid-template-columns:
      repeat(auto-fit, minmax(200px, 1fr));

      gap: 20px;
      margin-top: 25px;
    }

    .card {
      background: white;
      padding: 25px;
      border-radius: 15px;

      box-shadow:
      0 4px 10px rgba(0,0,0,0.15);
    }

    .value {
      font-size: 28px;
      font-weight: bold;
      margin-top: 10px;
    }
  </style>
</head>

<body>

  <div class="container">

    <h1>ESP32 Wi-Fi Weather Dashboard</h1>

    <p>Live Local Weather Station</p>

    <div class="cards">

      <div class="card">
        <h2>Temperature</h2>
        <div class="value" id="temperature">
          -- °C
        </div>
      </div>

      <div class="card">
        <h2>Humidity</h2>
        <div class="value" id="humidity">
          -- %
        </div>
      </div>

      <div class="card">
        <h2>Pressure</h2>
        <div class="value" id="pressure">
          -- hPa
        </div>
      </div>

      <div class="card">
        <h2>Altitude</h2>
        <div class="value" id="altitude">
          -- m
        </div>
      </div>

      <div class="card">
        <h2>Light Level</h2>
        <div class="value" id="light">
          -- %
        </div>
      </div>

    </div>

    <p>
      <b>Wi-Fi:</b>
      ESP32 Connected Network
    </p>

    <p>
      <b>ESP32 IP:</b>
      192.168.x.x
    </p>

  </div>

  <script>

    function updateData() {

      fetch('/data')

      .then(response => response.json())

      .then(data => {

        document.getElementById("temperature")
          .innerHTML =
          data.temp.toFixed(1) + " °C";

        document.getElementById("humidity")
          .innerHTML =
          data.humidity.toFixed(1) + " %";

        document.getElementById("pressure")
          .innerHTML =
          data.pressure.toFixed(1) + " hPa";

        document.getElementById("altitude")
          .innerHTML =
          data.altitude.toFixed(1) + " m";

        document.getElementById("light")
          .innerHTML =
          data.light + " %";

      });

    }

    updateData();

    setInterval(updateData, 5000);

  </script>

</body>

</html>
```

The ESP32 sends this page when the root URL `/` is requested:

```cpp
server.on(
  "/",
  HTTP_GET,
  []() {
    server.send(
      200,
      "text/html",
      buildHtmlPage()
    );
  }
);
```

Sensor data is provided through the `/data` endpoint in JSON format:

```json
{
  "temp": 29.70,
  "humidity": 83.60,
  "pressure": 1206.35,
  "altitude": 415.59,
  "light": 75
}
```

The JavaScript fetches this endpoint every five seconds to update the dashboard without requiring a full page reload.

## Setup Instructions

1. Connect the ESP32 and all sensors according to the wiring diagram.
2. Install the required Arduino libraries:

   * DHT sensor library
   * Adafruit Unified Sensor
   * Adafruit BMP280 Library
   * Adafruit GFX Library
   * Adafruit SSD1306
3. Open the project code in Arduino IDE.
4. Replace the Wi-Fi credentials:

```cpp
const char* ssid = "wifi name";
const char* password = "wifi password";
```

with your actual Wi-Fi network details.

5. Select the correct ESP32 board in Arduino IDE.
6. Select the correct COM port.
7. Upload the program to the ESP32.
8. Open the Serial Monitor at **115200 baud**.
9. Wait for the ESP32 to connect to Wi-Fi.
10. Copy the IP address printed in the Serial Monitor.
11. Open the IP address in a browser connected to the same Wi-Fi network.

## Local IP Address Format

The ESP32 receives a local IP address from the Wi-Fi router using DHCP.

The address normally follows this format:

```text
192.168.x.x
```

Example:

```text
192.168.1.105
```

The exact IP address depends on the local Wi-Fi network and may be different each time the ESP32 reconnects.

The Serial Monitor displays the address:

```text
Wi-Fi connected!
IP Address: 192.168.1.105
Web server started!
```

To access the dashboard, enter the IP address in the browser:

```text
http://192.168.1.105
```

The computer or smartphone and the ESP32 must be connected to the **same local Wi-Fi network** for the dashboard to be accessible.


## Project Working

The Wi-Fi Weather Dashboard combines multiple sensors with the ESP32's Wi-Fi capability. The DHT11 measures temperature and humidity, the BMP280 measures atmospheric pressure and estimates altitude, and the LDR detects the surrounding light level. The ESP32 processes the sensor readings and hosts a web dashboard that allows the data to be monitored remotely from a browser on the same Wi-Fi network.

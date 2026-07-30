# Project:  IoT Room Automation System

An ESP32-based IoT smart room automation system that combines environmental monitoring, automatic appliance control, safety alerts, OLED monitoring, and a Wi-Fi web dashboard for intelligent room management.

---
DRIVE LINK-https://drive.google.com/file/d/1GtKzSl5LkHXV6ZARSc8R-5OlHjelIvS1/view?usp=sharing
## 1. Project Overview
This project was developed as an IoT-based smart room automation system for a hostel room, classroom, office, or similar indoor environment.

The system monitors:

* Temperature and humidity
* Gas/smoke level
* Ambient light level
* Human presence using an ultrasonic sensor

Based on sensor readings, the system can:

* Automatically control a fan using temperature-based hysteresis
* Automatically control a light based on darkness and detected presence
* Trigger a gas safety alert
* Force all relays OFF during a gas alert
* Display sensor data and system status on an OLED
* Provide a web dashboard over Wi-Fi
* Provide manual override using push buttons
* Track system uptime

---

## 2. Components Used

* ESP32 Development Board
* DHT11 Temperature and Humidity Sensor
* MQ-2 Gas/Smoke Sensor
* LDR
* 10 kΩ Resistor for LDR voltage divider
* HC-SR04 Ultrasonic Sensor
* 2-Channel Relay Module
* 0.96-inch I2C OLED Display
* 3-Pin Active Buzzer Module
* Red LED
* Green LED
* Yellow LED
* 220 Ω LED Resistors
* 2 Push Buttons
* Breadboard
* Jumper Wires

---

## 3. System Architecture

```text
                 ┌─────────────────────┐
                 │       ESP32          │
                 │ Smart Room Automation│
                 │        System        │
                 └──────────┬──────────┘
                            │
       ┌────────────────────┼────────────────────┐
       │                    │                    │
       ▼                    ▼                    ▼
   DHT11                 MQ-2                 LDR
 Temperature           Gas/Smoke           Light Level
 Humidity              Detection           Detection
       │                    │                    │
       └────────────────────┼────────────────────┘
                            │
                            ▼
                    HC-SR04 Ultrasonic
                    Presence Detection
                            │
             ┌──────────────┼──────────────┐
             │              │              │
             ▼              ▼              ▼
          OLED          Relay 1         Relay 2
         Display          Fan            Light
             │
             ▼
       Wi-Fi Web Dashboard
```

---

# 4. Pin Connections

## DHT11

| DHT11 Pin | ESP32 |
| --------- | ----- |
| VCC       | 3.3V  |
| DATA      | GPIO4 |
| GND       | GND   |

---

## MQ-2 Gas Sensor

The MQ-2 is powered from 5V because the sensor module requires a higher supply voltage.

| MQ-2 Pin | Connection               |
| -------- | ------------------------ |
| VCC      | ESP32 VIN / 5V           |
| GND      | ESP32 GND                |
| AOUT     | Voltage divider → GPIO35 |

### MQ-2 Voltage Divider

The MQ-2 analog output can be higher than the safe input voltage of the ESP32 ADC.

The connection is:

```text
MQ-2 AOUT
     │
    10 kΩ
     │
     ├──────── GPIO35
     │
    10 kΩ
     │
    GND
```

The voltage divider reduces the voltage before it reaches the ESP32 GPIO35 ADC input.

---

## LDR

The LDR is connected as a voltage divider:

```text
3.3V
 │
LDR
 │
 ├──────── GPIO34
 │
10 kΩ resistor
 │
GND
```

The ESP32 reads the voltage at the middle point and maps the ADC value to a percentage.

---

## HC-SR04 Ultrasonic Sensor



.

| HC-SR04 Pin | ESP32                    |
| ----------- | ------------------------ |
| VCC         | VIN / 5V                 |
| GND         | GND                      |
| TRIG        | GPIO18                   |
| ECHO        | Voltage divider → GPIO19 |

### HC-SR04 Echo Voltage Divider

The HC-SR04 Echo pin can output approximately 5V, while ESP32 GPIO pins are designed for 3.3V logic.

Therefore:

```text
HC-SR04 ECHO
     │
    10 kΩ
     │
     ├──────── GPIO19
     │
    10 kΩ
     │
    GND
```

The Echo signal is reduced to a safer voltage before being connected to the ESP32.

### How the HC-SR04 Replaced the PIR

The HC-SR04 measures the distance to objects using ultrasonic sound waves.

The project uses the following logic:

```text
Distance < 150 cm
        ↓
Presence detected
```

If an object or person is detected within 150 cm, the system considers presence to be detected.

This was used for the light automation rule:

```text
Dark environment + Presence detected
              ↓
          Light ON
```

The HC-SR04 is not a direct motion sensor like a PIR. Instead, it detects the presence of an object within a specified distance. This was used as a practical replacement because the PIR sensor was unavailable.

---

# 5. Relay Connections

The relay module is active-LOW.

```text
LOW  = Relay ON
HIGH = Relay OFF
```

| Relay | ESP32 Pin | Function |
| ----- | --------- | -------- |
| IN1   | GPIO26    | Fan      |
| IN2   | GPIO27    | Light    |

The relays are initially turned OFF for safety when the ESP32 starts.

---

# 6. OLED Connections

The OLED uses I2C communication.

| OLED Pin | ESP32  |
| -------- | ------ |
| VCC      | 3.3V   |
| GND      | GND    |
| SDA      | GPIO21 |
| SCL      | GPIO22 |

The OLED cycles through three information screens:

### Screen 1: Climate

```text
Temperature
Humidity
```

### Screen 2: Sensors

```text
Gas Level
Light Level
Distance
Presence
```

### Screen 3: System

```text
Fan State
Light State
System Uptime
```

---

# 7. LED and Buzzer Connections

## Three-Pin Active Buzzer

| Buzzer Pin | ESP32  |
| ---------- | ------ |
| S / SIG    | GPIO14 |
| VCC / +    | 5V     |
| GND / -    | GND    |

The buzzer activates during a gas alert.

---

## Red LED

```text
GPIO25 → 220 Ω resistor → LED anode
LED cathode → GND
```

Function:

```text
Gas Alert = ON
Normal Operation = OFF
```

---

## Green LED

```text
GPIO2 → 220 Ω resistor → LED anode
LED cathode → GND
```

Function:

```text
System Normal = ON
Gas Alert = OFF
```

---

## Yellow LED

```text
GPIO33 → 220 Ω resistor → LED anode
LED cathode → GND
```

Function:

```text
Manual Override Active = ON
Automatic Mode = OFF
```

---

# 8. Push Button Connections

## Fan Manual Override

```text
One button terminal → GPIO0
Other button terminal → GND
```

## Light Manual Override

```text
One button terminal → GPIO32
Other button terminal → GND
```

The buttons use:

```cpp
INPUT_PULLUP
```

Therefore, pressing a button connects the GPIO pin to GND and produces a LOW signal.

---

# 9. Automation Rules

## Rule 1: Automatic Fan Control

The fan uses hysteresis to prevent rapid ON/OFF switching.

```text
Temperature > 32°C
        ↓
      Fan ON
```

```text
Temperature < 28°C
        ↓
      Fan OFF
```

The difference between the ON and OFF thresholds is called hysteresis.

This prevents the fan from continuously switching when the temperature is close to a single threshold.

---

## Rule 2: Automatic Light Control

The light turns ON when:

```text
Light level < 20%
AND
Presence detected
```

The light turns OFF when:

```text
Light level > 60%
```

or when no presence is detected for approximately 3 minutes.

Since the HC-SR04 was used instead of a PIR sensor, presence was determined using:

```text
Distance < 150 cm
```

---

## Rule 3: Gas/Smoke Safety Alert

When the gas reading crosses the configured threshold:

```text
Gas level > threshold
```

the system:

* Turns ON the red LED
* Turns ON the buzzer
* Turns OFF the green LED
* Forces the fan relay OFF
* Forces the light relay OFF
* Displays the alert through the system
* Prevents normal relay operation during the safety shutdown

This ensures that the system enters a safe state when a possible gas or smoke hazard is detected.

---

# 10. MQ-2 Threshold and Testing Explanation

The original project specification suggested using a threshold of:

```text
MQ-2 > 60%
```

During testing, the MQ-2 value did not reliably reach 60% during a controlled smoke demonstration.

Therefore, a threshold of:

```text
MQ-2 > 20%
```

was used for the practical demonstration.

This was done because the objective of the demonstration was to verify the complete safety-alert workflow:

```text
MQ-2 detects increased gas/smoke level
              ↓
        Gas alert triggered
              ↓
       Red LED + buzzer ON
              ↓
         All relays OFF
```

The threshold was lowered instead of using a lighter flame because using an open flame near the ESP32, breadboard, wiring, and other electronic components would create an unnecessary fire and safety risk.

The MQ-2 output used in this project is a mapped ADC value and is not a calibrated gas concentration in ppm. Therefore, the threshold is a project-specific detection threshold rather than a certified gas-safety limit.

---

# 11. Wi-Fi Web Dashboard

The ESP32 connects to the configured Wi-Fi network and starts a web server.

After connection, the Serial Monitor displays the ESP32 IP address:

```text
WiFi Connected
IP Address: 192.168.x.x
```

The dashboard can be opened by entering the IP address in a browser on the same Wi-Fi network:

```text
http://ESP32_IP_ADDRESS
```

Example:

```text
http://192.168.1.105
```

The dashboard displays:

* Temperature
* Humidity
* Gas level
* Light level
* Distance
* Presence status
* Fan state
* Light relay state
* Gas alert status
* System uptime

The dashboard also includes manual control buttons for the fan and light relay.

---

# 12. MQTT Status

MQTT publishing was implemented in the project code using the HiveMQ public broker and the configured project topic.

However, during final testing, MQTT communication experienced a connection/subscription glitch and reliable MQTT messages could not be demonstrated consistently.

Therefore, MQTT was **not used as a demonstrated working feature in the final project demonstration**.

The main working features demonstrated were:

* Sensor monitoring
* OLED display
* Automatic fan control
* Automatic light control
* HC-SR04 presence detection
* MQ-2 gas/smoke alert
* Red LED and buzzer safety alert
* Relay safety shutdown
* Wi-Fi web dashboard
* Manual override buttons
* System uptime tracking

MQTT remains a planned communication feature of the project architecture, but it was not claimed as a fully demonstrated working feature due to the observed communication glitch.

---

# 13. System Uptime

The system uses the ESP32 `millis()` function to track uptime.

The uptime is converted into:

```text
Days : Hours : Minutes
```

Example:

```text
0d 2h 35m
```

The uptime is displayed on:

* OLED
* Web dashboard

---

# 14. Testing Procedure

## DHT11 Test

Verify that the Serial Monitor displays:

```text
Temperature: XX.X C
Humidity: XX.X %
```

---

## MQ-2 Test

1. Allow the MQ-2 sensor to warm up.
2. Observe the normal gas reading.
3. Use a small controlled smoke source in a safe, ventilated environment.
4. Observe the gas percentage increasing.
5. When the configured threshold is crossed:

   * Red LED turns ON
   * Buzzer turns ON
   * Both relays turn OFF
   * Green LED turns OFF

---

## LDR Test

1. Observe the light percentage.
2. Cover the LDR.
3. Confirm that the light level changes.
4. If the environment is dark and presence is detected, the light relay should turn ON.

---

## HC-SR04 Test

1. Place an object or hand within 150 cm.
2. Confirm that presence is detected.
3. Move the object away.
4. Confirm that presence is no longer detected.

---

## Fan Test

The fan relay should:

```text
Temperature > 32°C → ON
Temperature < 28°C → OFF
```

The fan button can also be used for manual override.

---

## Light Test

The light relay should turn ON when:

```text
Light < 20%
AND
Presence detected
```

The light relay should turn OFF when:

```text
Light > 60%
```

or after the configured no-presence timeout.

---

# 15. Expected Serial Monitor Output

```text
IoT SMART ROOM AUTOMATION SYSTEM
HC-SR04 PRESENCE SENSOR

WiFi Connected
IP Address: 192.168.x.x

WEB SERVER STARTED
SYSTEM READY

====================
SENSOR DATA
====================
Temperature: 29.0 C
Humidity: 76.0 %
Gas: 12 %
Light: 18 %
Distance: 75.0 cm
Presence: DETECTED
```

During a gas alert:

```text
!!! GAS ALERT !!!
BUZZER ON
RED LED ON
ALL RELAYS FORCED OFF
```

---

# 16. Project Limitations

* A PIR sensor was unavailable, so the HC-SR04 was used for presence detection.
* The HC-SR04 detects the presence of an object within a distance range rather than detecting motion in the same way as a PIR sensor.
* The MQ-2 gas value is based on a mapped ADC reading and is not calibrated in ppm.
* A lower gas threshold was used for the controlled demonstration because the original 60% threshold was not reliably reached during testing.
* MQTT was implemented in the code but was not demonstrated as a working feature because of a communication/subscription glitch during final testing.
* The relay outputs are simulated for fan and light control and should be connected to mains appliances only with proper electrical safety precautions.

---

# 17. Conclusion

This project combines multiple IoT concepts into a single ESP32-based smart room automation system.

The system successfully integrates:

```text
Sensors
   ↓
ESP32 Processing
   ↓
Automation Rules
   ↓
Relays + LEDs + Buzzer
   ↓
OLED Monitoring
   ↓
Wi-Fi Web Dashboard
```

The project demonstrates how multiple sensors can be integrated to automate a room by monitoring environmental conditions, controlling appliances automatically, providing manual override, and ensuring safety through gas detection and emergency shutdown.


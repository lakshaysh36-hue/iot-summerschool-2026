# Project 3: Ultrasonic Parking Assistant
I HAVE USED GREEN LED HERE AS YELLOW LED WAS NOT AVAILABLE AT THE TIME
GOOGLE DRIVE LINK-https://drive.google.com/file/d/1-aLXYVMHvsnAdSsm0y9SWm-wAqEp-ipP/view?usp=drivesdk
## Components Used

* Arduino UNO
* HC-SR04 Ultrasonic Distance Sensor
* 0.96-inch I2C OLED Display (128×64)
* Green LED
* Yellow LED
* Red LED
* Buzzer
* Resistors for LEDs
* Breadboard
* Jumper wires
* USB cable

## Wiring Summary

### HC-SR04 Ultrasonic Sensor

| HC-SR04 Pin | Arduino UNO    |
| ----------- | -------------- |
| VCC         | 5V             |
| GND         | GND            |
| TRIG        | Digital Pin 9  |
| ECHO        | Digital Pin 10 |

### OLED Display (I2C)

| OLED Pin | Arduino UNO |
| -------- | ----------- |
| VCC      | 5V          |
| GND      | GND         |
| SDA      | A4          |
| SCL      | A5          |

### Buzzer

| Buzzer Pin   | Arduino UNO   |
| ------------ | ------------- |
| Positive (+) | Digital Pin 6 |
| Negative (-) | GND           |

### LEDs

| LED        | Arduino UNO Pin |
| ---------- | --------------- |
| Green LED  | Digital Pin 11  |
| Yellow LED | Digital Pin 12  |
| Red LED    | Digital Pin 13  |

Each LED should be connected through an appropriate current-limiting resistor.

## How to Run

1. Connect all components according to the wiring summary.
2. Install the required Arduino libraries:

   * `Adafruit GFX Library`
   * `Adafruit SSD1306`
3. Open the Arduino IDE.
4. Select:

   * **Board:** Arduino UNO
   * **Correct COM Port:** Arduino UNO port
5. Upload the program.
6. Open the Serial Monitor at **9600 baud**.
7. Place an object in front of the HC-SR04 ultrasonic sensor.
8. Move the object closer or farther away to observe the changes in:

   * Distance measurement
   * OLED display
   * LED indicators
   * Buzzer alert pattern
9. The system averages five ultrasonic readings to provide more stable distance measurements.

## Expected Output

The system measures the distance between the ultrasonic sensor and an object and classifies the distance into four zones.

### SAFE — More than 60 cm

* Green LED: ON
* Yellow LED: OFF
* Red LED: OFF
* Buzzer: OFF
* OLED displays the distance and `SAFE`

Example:


Distance: 85.4 cm | Zone: SAFE


### CAUTION — 30 cm to 60 cm

* Green LED: OFF
* Yellow LED: ON
* Red LED: OFF
* Buzzer: Slow intermittent beep
* OLED displays `CAUTION`

Example:


Distance: 45.2 cm | Zone: CAUTION


### CLOSE — 15 cm to less than 30 cm

* Green LED: OFF
* Yellow LED: ON
* Red LED: ON
* Buzzer: Faster beeping
* OLED displays `CLOSE`

Example:


Distance: 22.7 cm | Zone: CLOSE


### DANGER — Less than 15 cm

* Green LED: OFF
* Yellow LED: OFF
* Red LED: ON
* Buzzer: Continuous high-frequency alarm
* OLED displays `DANGER`

Example:


Distance: 8.5 cm | Zone: DANGER

## Physics Formula Used for Distance Calculation

The HC-SR04 ultrasonic sensor calculates distance using the **time-of-flight principle**.

The sensor sends an ultrasonic pulse and measures the time taken for the echo to return after reflecting from an object.



The fundamental relationship is:


Distance = Speed × Time


However, the ultrasonic pulse travels:


Sensor → Object → Sensor

Therefore, the measured time represents the **round-trip time**. The actual one-way distance is calculated as:

Distance = (Speed of Sound × Time) / 2


### Formula Used in the Code

The code uses:


float distance = duration * 0.034 / 2;


Where

* `duration` = echo travel time in microseconds
* `0.034` = approximate speed of sound in centimeters per microsecond
* `/ 2` = divides the round-trip distance by two to obtain the one-way distance

The speed of sound is approximately:


343 m/s


This is equivalent to approximately:


0.0343 cm/µs


Therefore:


Distance (cm) = duration (µs) × 0.0343 / 2


### Example Calculation

If the HC-SR04 measures an echo time of:


1000 µs


Then:

Distance = (1000 × 0.034) / 2
Distance = 17 cm


Therefore, the object is approximately **17 cm** away from the sensor.

### Why the Distance Is Divided by 2

The ultrasonic pulse travels twice the distance:


Sensor ─────────► Object
       Distance

Sensor ◄───────── Object
       Distance


The measured time includes both journeys:


Total distance = 2 × Actual distance


Therefore:


Actual distance = Total distance / 2


### Averaging Multiple Readings

The project takes five distance measurements and calculates their average:


float getAverageDistance() {

  float total = 0;

  for (int i = 0; i < 5; i++) {
    total += measureDistance();
    delay(10);
  }

  return total / 5.0;
}


Mathematically:


Average Distance =
(D₁ + D₂ + D₃ + D₄ + D₅) / 5

Averaging helps reduce small fluctuations caused by sensor noise and reflections, resulting in a more stable parking distance measurement.



## Project Working

The HC-SR04 sensor sends an ultrasonic pulse and measures the time taken for the echo to return. The Arduino UNO converts this time into distance. Five readings are averaged to reduce measurement fluctuations.

Based on the measured distance, the system changes the LED indicators and buzzer behavior. The OLED displays the real-time distance, current parking zone, and a proximity bar. The current distance and zone are also printed to the Serial Monitor.

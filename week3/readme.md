## Library Used

**Adafruit DHT Sensor Library**

Version: 1.4.6

Also requires:
- Adafruit Unified Sensor Library
CSV output
*/Serial.print(millis());
Serial.print(",");
Serial.print(tempC);
Serial.print(",");
Serial.print(tempF);
Serial.print(",");
Serial.println(humidity);
/*
//timestamp,temp_C,temp_F,humidity
//example
//4000,30.5,86.9,62

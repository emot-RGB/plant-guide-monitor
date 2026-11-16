//#include "esp32-hal-adc.h"
//#include "esp32-hal-gpio.h"
#pragma once

#include <Arduino.h>

#define SHPIN 4

class SHSensor {

public:
  float soil_humidity;

  SHSensor() {
    soil_humidity = 0;
  };
  void begin() {
    pinMode(SHPIN, INPUT);
  };
  void update() {
    soil_humidity = map(analogRead(SHPIN), 65, 2350, 0, 100);
    if (soil_humidity < 0)
      soil_humidity = 0;
    else if (soil_humidity > 100) soil_humidity = 100;
  };
  void println() {
    Serial.print("Soil Humidity: ");
    Serial.print(soil_humidity);
    Serial.print("\n");
  };
};

// example code
/*


#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 7     // Digital pin connected to the AM2302/DHT22 data pin
#define DHTTYPE DHT22   // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("AM2302/DHT22 Sensor Test"));

  dht.begin();
}

void loop() {
  // Wait 2 seconds between measurements (sensor update rate is ~0.5 Hz)
  delay(2000);

  // Read temperature or humidity takes about 250 milliseconds
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from AM2302 sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C / "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C / "));
  Serial.print(hif);
  Serial.println(F("°F"));
}


*/

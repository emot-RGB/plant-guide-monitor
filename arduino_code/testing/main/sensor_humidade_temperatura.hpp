#pragma once

#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 2       // Digital pin connected to the AM2302/DHT22 data pin
#define DHTTYPE DHT22  // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

class HTSensor {

public:
  float humidity;
  float temperature;

  HTSensor() {
    humidity = 0;
    temperature = 0;
  };
  void begin() {
    dht.begin();
  };
  void update() {

    // Read temperature or humidity takes about 250 milliseconds
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();

    static unsigned long error_cooldown;
    if (isnan(h) || isnan(t)) {
      if (millis() - error_cooldown > 50000) {
        Serial.println(F("Failed to read from AM2302 sensor!"));
        error_cooldown = millis();
      }
      return;
    }
    temperature = t;
    humidity = h;
  };
  void println() {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%  Temperature: ");
    Serial.print(temperature);
    Serial.print("°C / \n");
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

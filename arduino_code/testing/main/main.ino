#include "sensor_humidade_temperatura.hpp"


HTSensor sensor;

void setup() {
  Serial.begin(9600);
  Serial.println(F("AM2302/DHT22 Sensor Test"));
  sensor.begin();
}

void loop() {
  // Wait 2 seconds between measurements (sensor update rate is ~0.5 Hz)
  delay(2000);


  sensor.update();
  sensor.println();
  


}

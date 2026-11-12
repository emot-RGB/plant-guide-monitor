
#include "wifi_config.hpp"
#include "server.hpp"










WifiConfig wifi;
SystemControlServer system_server;

void setup() {
  wifi.begin();
  Serial.begin(9600);
  Serial.println(F("AM2302/DHT22 Sensor Test"));

  system_server.begin();
}

void loop() {
  system_server.handleClient();
 
  wifi.update();

}

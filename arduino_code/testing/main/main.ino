
#include "wifi_config.hpp"
#include "server.hpp"










WifiConfig wifi;
SystemControlServer system_server;

void setup() {
  Serial.begin(9600);
  Serial.println(F("AM2302/DHT22 Sensor Test"));

  wifi.begin();
  system_server.begin();
}

void loop() {
  system_server.handleClient();
 
  wifi.update();

}

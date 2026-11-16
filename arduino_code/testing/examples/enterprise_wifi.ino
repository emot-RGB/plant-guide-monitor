#include <WiFi.h>
#include <WiFiEnterprise.h> // Depending on the library wrapper version

const char* ssid = "your-enterprise-ssid";
const char* username = "your-username";
const char* password = "your-password";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Begin EAP-PEAP connection
  // Note: implementation details depend on the specific enterprise library version used
  WiFi.begin(ssid, username, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

void loop() {}

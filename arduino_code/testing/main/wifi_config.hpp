#pragma once

//#include "esp32-hal.h"
#include <Arduino.h>
#include <WiFi.h>
#include "../credencials.hpp"


const char* ssid = "ESP_Server";
const char* password = "12345678";





class WifiConfig {
public:
  const char* local_ssid;
  const char* local_password;

  const char* host_ssid;
  const char* host_password;

  WifiConfig() {
  }

  void begin() {
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.softAP(ssid, password);

    Serial.println("\n\nesp32 host network");
    // Print the IP address of the server
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    WiFi.begin(ssidl, passwordl);
    // Print the IP address of the server
  }



  void update() {
    static unsigned long time;
    static bool connected;
    if (connected)return;
    if (WiFi.status() != WL_CONNECTED && millis() - time > 1000) {
      Serial.println("no local network connected");
      time = millis();

    } else if (connected == false && WiFi.status() == WL_CONNECTED) {
      connected = true;
      Serial.println("\n\nLocal network Access Point Started");
      Serial.print("Local IP Address: ");
      Serial.println(WiFi.localIP());
    }
  }
};

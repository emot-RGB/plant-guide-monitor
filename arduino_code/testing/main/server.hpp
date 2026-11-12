#pragma once

#include "sensor_humidade_temperatura.hpp"
#include <Arduino.h>
#include <WebServer.h>
WebServer server(80);


// HTML page template - What is displayed on browsers and respective actions
const char jsonSensorData[] PROGMEM = R"rawliteral(
    {
      "record": {
        "sensors": {
          "temperature": {
            "value": tv,
            "unit": "ºC"
          },
          "humidity": {
            "value": hv,
            "unit": "%"
          }
        }
      }
    }

)rawliteral";







class SystemControlServer {
public:

  HTSensor htsensor;
  float soil_humidity;



  SystemControlServer() {}

  void begin() {

    htsensor.begin();

    server.on("/get_latest_record", [this]() {
      this->send_latest_record();
    });
    // Start the webserver
    server.begin();
    Serial.println("HTTP server started");
  }

  void handleClient() {
    server.handleClient();
    htsensor.update();
  }

private:

  void send_latest_record() {
    String message = jsonSensorData;
    message.replace("tv", String(htsensor.temperature));
    message.replace("hv", String(htsensor.humidity));
    server.send(200, "text/plain", message);
  }
};

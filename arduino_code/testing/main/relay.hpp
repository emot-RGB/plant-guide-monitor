#pragma once

#include <Arduino.h>

#define PUMP_PIN 10  // Pino digital do ESP32 ligado ao 'IN' do relé da bomba

class Pump {
public:
  bool is_on;

  Pump() {
    is_on = false;
  }

  void begin() {
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, LOW); // Garante que arranca desligada por segurança
    is_on = false;
  }

  void update(float soil_humidity) {
    // Lógica automática de rega baseada na humidade do solo (< 30% liga, > 75% desliga, etc.)
    if (soil_humidity < 30.0) {
      ligar();
    } else if (soil_humidity >= 70.0) {
      desligar();
    }
  }

  void ligar() {
    digitalWrite(PUMP_PIN, HIGH); // Altera para LOW se o teu relé for Active-LOW
    is_on = true;
  }

  void desligar() {
    digitalWrite(PUMP_PIN, LOW);  // Altera para HIGH se o teu relé for Active-LOW
    is_on = false;
  }

  void println() {
    Serial.print("Pump Status: ");
    Serial.println(is_on ? "ON (Regando)" : "OFF");
  }
};

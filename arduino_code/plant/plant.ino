#include "DHT.h"

// --- DEFINIÇÕES DE HARDWARE ---
#define DHTPIN 4          
#define DHTTYPE DHT22     
#define SOIL_PIN 1        

// --- DEFINIÇÕES DOS LEDS E RELÉ ---
#define LED_VERMELHO 6    
#define LED_VERDE 7       
#define LED_AZUL 8        
#define RELAY_PIN 10      

// VALORES DE CALIBRAÇÃO REAIS 
const int VALOR_SECO = 50;       
const int VALOR_MOLHADO = 1800;  

// Criação do objeto 'dht' 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("PGM - Sistema Completo com Alertas e Bomba");
  
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  digitalWrite(RELAY_PIN, LOW);
  
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature(); 
  float hum = dht.readHumidity();     

  int valorSoloRaw = analogRead(SOIL_PIN);
  int humidadeSoloPct = map(valorSoloRaw, VALOR_SECO, VALOR_MOLHADO, 0, 100);
  humidadeSoloPct = constrain(humidadeSoloPct, 0, 100);

  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AZUL, LOW);

  if (humidadeSoloPct < 30) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(RELAY_PIN, HIGH);
  } 
  else if (humidadeSoloPct >= 30 && humidadeSoloPct <= 75) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(RELAY_PIN, LOW);
  } 
  else {
    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(RELAY_PIN, LOW);
  }

  if (isnan(temp) || isnan(hum)) {
    Serial.println("[ERRO] Falha na leitura do sensor DHT22!");
  } else {
    Serial.print("Temp Ar: "); Serial.print(temp); Serial.print(" °C | ");
    Serial.print("Hum Ar: "); Serial.print(hum); Serial.print(" % | ");
    Serial.print("Solo Bruto: "); Serial.print(valorSoloRaw); Serial.print(" | ");
    Serial.print("Hum Solo: "); Serial.print(humidadeSoloPct); Serial.print("% | ");
    
    if (humidadeSoloPct < 30) {
      Serial.println("ESTADO: Falta de Água 🔴 (A REGAR...)");
    } else if (humidadeSoloPct >= 30 && humidadeSoloPct <= 75) {
      Serial.println("ESTADO: Nível Ideal 🟢");
    } else {
      Serial.println("ESTADO: Excesso de Água 🔵");
    }
  }

  delay(4000);
}

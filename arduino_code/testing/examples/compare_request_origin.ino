#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

void handleRoot() {
  WiFiClient client = server.client();
  IPAddress clientIP = client.remoteIP();
  IPAddress localIP = client.localIP(); // The ESP32 IP that received the request

  String networkSource = "Unknown";

  // Method A: Compare the local IP that received the request
  if (localIP == WiFi.softAPIP()) {
    networkSource = "ESP32 Access Point (AP)";
  } else if (localIP == WiFi.localIP()) {
    networkSource = "Home Wi-Fi Router (STA)";
  }

  Serial.print("Request came from network: ");
  Serial.println(networkSource);
  Serial.print("Client IP: ");
  Serial.println(clientIP);

  server.send(200, "text/plain", "Connected via: " + networkSource);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESP32-Setup");
  WiFi.begin("Your_WiFi_SSID", "Your_WiFi_Password");

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}

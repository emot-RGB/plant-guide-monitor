#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
WebServer server(80);





const char* ssid = "ESP_Server";
const char* password = "12345678";

const char* ssidl = "kevin";
const char* passwordl = "quevin1233";




// Internal RGB values
int Red = 0;
int Green = 0;
int Blue = 255;




// HTML page template - What is displayed on browsers and respective actions
const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body { font-family: Arial; text-align: center; margin-top: 40px; }
input { width: 80px; padding: 8px; font-size: 16px; margin: 4px; }
label { font-weight: bold; margin-right: 4px; }
h3 { margin-top: 30px; }
</style>
</head>
<body>
<h2>ESP RGB Controller</h2>
<p id="currentColor">Current LED RGB color: %R%, %G%, %B%</p>
<h3>Please input the RGB values for the LED</h3>
<div>
<label>R:</label><input type="number" id="rVal" min="0" max="255" value="%R%"
onchange="updateValue()"><br>
<label>G:</label><input type="number" id="gVal" min="0" max="255" value="%G%"
onchange="updateValue()"><br>
<label>B:</label><input type="number" id="bVal" min="0" max="255" value="%B%"
onchange="updateValue()">
</div>
<script>
function updateValue() {
let r = document.getElementById('rVal').value;
let g = document.getElementById('gVal').value;
let b = document.getElementById('bVal').value;
fetch(`/setRGB?r=${r}&g=${g}&b=${b}`)
.then(response => response.text())
.then(text => {
document.getElementById('currentColor').innerText = text;
});
}
</script>
</body>
</html>
)rawliteral";


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




// Function to handle the main page (root page) - http://192.168.4.1/
void handleRoot() {
  String page = htmlPage;
  // Replace placeholders
  page.replace("%R%", String(Red));
  page.replace("%G%", String(Green));
  page.replace("%B%", String(Blue));
  server.send(200, "text/html", page);
}

// Function to handle the main page (root page) - http://192.168.4.1/
void handleRootSensorDataRequest() {
  String page = jsonSensorData;
  // Replace placeholders
  page.replace("%R%", String(Red));
  page.replace("%G%", String(Green));
  page.replace("%B%", String(Blue));
  server.send(200, "text/json", page);
}




// Function to handle the update of RGB values - http://192.168.4.1/setrgb
void handleSetRGB() {
  if (server.hasArg("r")) Red = server.arg("r").toInt();
  if (server.hasArg("g")) Green = server.arg("g").toInt();
  if (server.hasArg("b")) Blue = server.arg("b").toInt();
  Serial.printf("Updated values -> R:%d, G:%d, B:%d\n", Red, Green, Blue);
  String msg = "Current LED RGB color: " + String(Red) + ", " + String(Green) + ", " + String(Blue);
  server.send(200, "text/plain", msg);
}



void setup() {
  Serial.begin(115200);
  // Create a Wifi hotspot
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  // Print the IP address of the server
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  WiFi.begin(ssidl, passwordl);
  // Print the IP address of the server
  do {
    delay(2000);
    Serial.println("._.");
  } while (WiFi.status() != WL_CONNECTED);
  Serial.println("Local network Access Point Started");
  Serial.print("Local IP Address: ");
  Serial.println(WiFi.localIP());


  // Set the functions that handle requests to the root webpage and to the /setRGB endpoint
  server.on("/", handleRoot);
  server.on("/setRGB", handleSetRGB);
  // Start the webserver
  server.begin();
  Serial.println("HTTP server started");
}



void loop() {
  // handle requests to the webserver
  server.handleClient();
}

/*
 * lab5part3.ino
 *
 * Responds to HTTP /ping?value=X with JSON {"mtype":"pong","value":X+1,"millis":...}
 * Uses MIME type application/json.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-20
 * Modified: 2025-04-24
 */

#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// === WiFi Credentials ===
const char* SSID = "BBBTB";
const char* PASSWORD = "7202568872";

// === Constants ===
const int BAUD_RATE = 115200;
const int WIFI_WAIT_MS = 100;

// === Global Server Object ===
WebServer g_server(80);

// === Setup Function ===
void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial) continue;
  Serial.println("Serial connected");

  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(WIFI_WAIT_MS);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  g_server.on("/ping", HTTP_handlePing);
  g_server.onNotFound(HTTP_notFound);

  g_server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  g_server.handleClient();
}

// === 404 Handler ===
void HTTP_notFound() {
  Serial.printf("%lu\t404\tNot Found\t%s\n", millis(), g_server.uri().c_str());
  g_server.send(404, "text/html", "404 Not Found");
}

// === JSON Pong Response ===
void HTTP_handlePing() {
  Serial.printf("%lu\t200\t%s\n", millis(), g_server.uri().c_str());

  // Parse query string
  int value = 0;
  bool hasValue = false;

  if (g_server.hasArg("value")) {
    value = g_server.arg("value").toInt(); // Will return 0 if not a number
    hasValue = true;
  }

  // Create JSON response
  StaticJsonDocument<256> doc;
  doc["mtype"] = "pong";
  doc["value"] = value + 1;
  doc["millis"] = millis();

  // Serialize to string
  String jsonResponse;
  serializeJson(doc, jsonResponse);

  // Send JSON response
  g_server.send(200, "application/json", jsonResponse);
  delay(1); // Helps keep connection stable
}

/*
 * lab5part2.ino
 *
 * Sets up a basic HTTP server on ESP32-C3.
 * Responds to /ping and handles unknown routes.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-25
 */

#include <WiFi.h>
#include <WebServer.h>

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
  // Set up Serial I/O
  Serial.begin(BAUD_RATE);
  while (!Serial) continue;
  Serial.println("Serial connected");

  // Connect to Wi-Fi
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(WIFI_WAIT_MS);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Configure HTTP server routes
  g_server.on("/ping", HTTP_handlePing);
  g_server.onNotFound(HTTP_notFound);

  // Start server
  g_server.begin();
  Serial.println("HTTP server started");
}

// === Loop Function ===
void loop() {
  g_server.handleClient();
}

// === 404 Handler ===
void HTTP_notFound() {
  Serial.printf("%lu\t404\tNot Found\t%s\n", millis(), g_server.uri().c_str());
  g_server.send(404, "text/html", "404 Not Found");
}

// === Ping Handler ===
void HTTP_handlePing() {
  Serial.printf("%lu\t200\t%s\n", millis(), g_server.uri().c_str());
  String value = "unknown";

  if (g_server.hasArg("value")) {
    value = g_server.arg("value");
  }

  Serial.printf("DEBUG: the value is: '%s'\n", value.c_str());

  // Format HTML response
  String prefix("<html><head><title>Pong</title></head><body>");
  String suffix("</body></html>");
  String response = prefix + "<h1>Pong</h1>The value is <em>" + value + "</em>" + suffix;

  // Send response
  g_server.setContentLength(response.length());
  g_server.send(200, "text/html", response);
  delay(1); // Optional: helps prevent dropped responses
}

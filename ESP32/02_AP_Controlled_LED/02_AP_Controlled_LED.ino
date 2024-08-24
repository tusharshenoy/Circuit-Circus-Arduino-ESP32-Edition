#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "ESP32-AP";
const char *password = "12345678";

WebServer server(80);
const int ledPin = 4;

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1><p><a href=\"/LED_ON\"><button>LED ON</button></a></p><p><a href=\"/LED_OFF\"><button>LED OFF</button></a></p>");
}

void handleLEDOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/html", "<h1>LED is ON</h1><p><a href=\"/LED_OFF\"><button>Turn OFF</button></a></p>");
}

void handleLEDOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", "<h1>LED is OFF</h1><p><a href=\"/LED_ON\"><button>Turn ON</button></a></p>");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Set up Access Point
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Define routes
  server.on("/", handleRoot);
  server.on("/LED_ON", handleLEDOn);
  server.on("/LED_OFF", handleLEDOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

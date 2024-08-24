#include <WiFi.h>

const char* ssid = "Hehe";         // Replace with your Wi-Fi network name
const char* password = "123456789"; // Replace with your Wi-Fi password

WiFiServer server(80); // Start a server on port 80

const int ledPin = 4; // LED connected to GPIO 2

void setup() {
  pinMode(ledPin, OUTPUT);  // Set the LED pin as an output
  digitalWrite(ledPin, LOW); // Turn off the LED initially

  // Connect to Wi-Fi
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to Wi-Fi!");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin(); // Start the server
}

void loop() {
  WiFiClient client = server.available(); // Check if a client has connected

  if (client) {
    String request = client.readStringUntil('\r'); // Read the client's request
    client.flush(); // Clear the client buffer

    // Check if the request is to turn the LED on or off
    if (request.indexOf("/LED=ON") != -1) {
      digitalWrite(ledPin, HIGH); // Turn on the LED
    }
    if (request.indexOf("/LED=OFF") != -1) {
      digitalWrite(ledPin, LOW); // Turn off the LED
    }

    // Send the HTML response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<html><body>");
    client.println("<h1>ESP32 LED Control</h1>");
    client.println("<p><a href=\"/LED=ON\"><button>Turn ON</button></a></p>");
    client.println("<p><a href=\"/LED=OFF\"><button>Turn OFF</button></a></p>");
    client.println("</body></html>");
    
    delay(1);
    client.stop(); // Close the connection
  }
}

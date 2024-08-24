#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int ledPin = 4; // LED connected to GPIO

void setup() {
  pinMode(ledPin, OUTPUT);  // Set the LED pin as an output
  digitalWrite(ledPin, LOW); // Turn off the LED initially

  Serial.begin(115200); // Start the Serial Monitor
  SerialBT.begin("ESP32_LED_Control"); // Start Bluetooth with a name

  Serial.println("Bluetooth device is ready to pair.");
}

void loop() {
  if (SerialBT.available()) { // Check if there is any data available to read
    char command = SerialBT.read(); // Read the command

    if (command == '1') { // If the command is '1'
      digitalWrite(ledPin, HIGH); // Turn on the LED
      Serial.println("LED ON");
    }
    else if (command == '0') { // If the command is '0'
      digitalWrite(ledPin, LOW); // Turn off the LED
      Serial.println("LED OFF");
    }
  }
}

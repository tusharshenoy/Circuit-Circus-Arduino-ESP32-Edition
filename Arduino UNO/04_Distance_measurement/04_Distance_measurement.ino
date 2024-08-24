#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with the I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Ultrasonic Sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Buzzer pin
const int buzzerPin = 6;

// Variables for calculating distance
long duration;
int distance;

void setup() {
  lcd.init();            // Initialize the LCD
  lcd.backlight();       // Turn on the backlight
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.print("Distance:");  // Initial display
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distance = duration * 0.034 / 2;

  // Display the distance on the LCD
  lcd.setCursor(0, 1);  // Move to the second line
  lcd.print("            "); // Clear previous distance
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  // Beep based on the distance
  if (distance < 20) {
    tone(buzzerPin, 1000); // Long beep
    delay(1000);
    noTone(buzzerPin);
    delay(100);
  } else if (distance >= 20 && distance < 40) {
    tone(buzzerPin, 1000); // Fast beep
    delay(100);
    noTone(buzzerPin);
    delay(100);
  } else if (distance >= 40 && distance < 60) {
    tone(buzzerPin, 1000); // Medium beep
    delay(500);
    noTone(buzzerPin);
    delay(500);
  } else {
    noTone(buzzerPin); // No beep
  }

  delay(100); // Short delay before the next loop
}

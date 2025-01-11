#define BLYNK_TEMPLATE_ID "TMPL5ysohikeg"
#define BLYNK_TEMPLATE_NAME "Smart Street Light"

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
 
// Pin Definitions
#define TFT_CS    5
#define TFT_RST   2
#define TFT_DC    4
#define TFT_SCLK  18
#define TFT_MOSI  23
#define LDR_PIN 34
#define PIR_PIN_1 25
#define PIR_PIN_2 26
#define PIR_PIN_3 27
#define LED_PIN_1 12
#define LED_PIN_2 13
#define LED_PIN_3 14
#define BUZZER_PIN 32
#define BUTTON_PIN 33
 
// Initialize ST7789 display
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Blynk Auth Token
char auth[] = "PvJ9Myrxu_WIWGto7ZzhYXl3rS5lacdE";
 
// Your WiFi credentials
char ssid[] = "huwai nova j7";
char pass[] = "laxmi@755";
 
// Global variables
bool buzzerOn = false; // Flag to track the state of the buzzer
int prevLightIntensity = 0; // Variable to store the previous light intensity
 
BlynkTimer timer;
 
// Blynk virtual pin assignments
#define VIRTUAL_BUTTON V0
#define VIRTUAL_LED1 V1
#define VIRTUAL_LED2 V2
#define VIRTUAL_LED3 V3
#define VIRTUAL_BUZZER V4
#define VIRTUAL_LDR V5
#define VIRTUAL_PIR1 V6
#define VIRTUAL_PIR2 V7
#define VIRTUAL_PIR3 V8
 
void setup() {
  // Initialize Serial communication
  Serial.begin(115200);
 
  // Set pin modes
  pinMode(LDR_PIN, INPUT);
  pinMode(PIR_PIN_1, INPUT);
  pinMode(PIR_PIN_2, INPUT);
  pinMode(PIR_PIN_3, INPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
 
  // Initialize ST7789 display
  tft.init(240, 320);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
 
  // Connect to WiFi and Blynk
  Blynk.begin(auth, ssid, pass);
 
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensorData);
}
 
void loop() {
  Blynk.run();
  timer.run();
}
 
// Blynk virtual button handler
BLYNK_WRITE(VIRTUAL_BUTTON) {
  int buttonState = param.asInt();
  buzzerOn = (buttonState == 1);
  if (buzzerOn) {
    tone(BUZZER_PIN, 1000); // Emit a 1000 Hz tone
    Serial.println("Buzzer ON");
    Blynk.virtualWrite(VIRTUAL_BUZZER, 1);
  } else {
    noTone(BUZZER_PIN);
    Serial.println("Buzzer OFF");
    Blynk.virtualWrite(VIRTUAL_BUZZER, 0);
  }
}
 
// Function to send sensor data to Blynk
void sendSensorData() {
  // Read light intensity from LDR pin
  int lightIntensity = analogRead(LDR_PIN);
 
  // Send light intensity to Blynk
  Blynk.virtualWrite(VIRTUAL_LDR, lightIntensity);
 
  // Display light intensity on LCD if it has changed
  if (lightIntensity != prevLightIntensity) {
    // Clear previous light intensity reading
    tft.fillRect(0, 0, 240, 20, ST77XX_BLACK);
    // Print new light intensity reading
    tft.setCursor(0, 0);
    tft.print("Light Intensity: ");
    tft.println(lightIntensity);
    // Update previous light intensity
    prevLightIntensity = lightIntensity;
  }
 
  // Read PIR sensor values
  bool pirStatus1 = digitalRead(PIR_PIN_1);
  bool pirStatus2 = digitalRead(PIR_PIN_2);
  bool pirStatus3 = digitalRead(PIR_PIN_3);
 
  // Send PIR sensor values to Blynk
  Blynk.virtualWrite(VIRTUAL_PIR1, pirStatus1);
  Blynk.virtualWrite(VIRTUAL_PIR2, pirStatus2);
  Blynk.virtualWrite(VIRTUAL_PIR3, pirStatus3);
 
  // Display which PIR sensor detects an object
  tft.fillRect(0, 40, 240, 60, ST77XX_BLACK); // Clear previous PIR sensor status
  tft.setCursor(0, 40);
  tft.print("PIR 1: ");
  tft.println(pirStatus1 ? "DETECTED" : "NOT DETECTED");
  tft.setCursor(0, 60);
  tft.print("PIR 2: ");
  tft.println(pirStatus2 ? "DETECTED" : "NOT DETECTED");
  tft.setCursor(0, 80);
  tft.print("PIR 3: ");
  tft.println(pirStatus3 ? "DETECTED" : "NOT DETECTED");
 
  // Control LEDs through Blynk
  Blynk.virtualWrite(VIRTUAL_LED1, pirStatus1);
  Blynk.virtualWrite(VIRTUAL_LED2, pirStatus2);
  Blynk.virtualWrite(VIRTUAL_LED3, pirStatus3);
 
  if (buzzerOn) {
    // Turn on all LEDs if the buzzer is on
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, HIGH);
    digitalWrite(LED_PIN_3, HIGH);
  } else {
    // Control LEDs based on PIR sensors if the buzzer is off
    digitalWrite(LED_PIN_1, pirStatus1);
    digitalWrite(LED_PIN_2, pirStatus2);
    digitalWrite(LED_PIN_3, pirStatus3);
  }
 
  // Clear emergency alert message only if needed
  if (!buzzerOn) {
    tft.fillRect(0, 20, 240, 20, ST77XX_BLACK);
  }
 
  // Display emergency alert if buzzer is on
  if (buzzerOn) {
    tft.setCursor(0, 20);
    tft.println("EMERGENCY ALERT!");
  }
}
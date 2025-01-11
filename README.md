# Smart_street_light

The Smart Street Light is an IoT-based project that controls street lights with sensors such as Light Dependent Resistor (LDR) and Passive Infrared (PIR) sensors. The system can monitor light intensity, detect motion, and control the streetlights and an emergency buzzer through a mobile app (via the Blynk platform).

# Features
Light Intensity Detection: Uses an LDR sensor to detect the surrounding light intensity and adjust the street light accordingly.

Motion Detection: Uses three PIR sensors to detect movement and control the state of streetlights based on detected activity.

Emergency Alert: A buzzer sounds when triggered, signaling an emergency. The system will also turn on all the streetlights.

Real-Time Control: Control the streetlight status and buzzer from anywhere via the Blynk app.

Live Display: Displays sensor data (light intensity and PIR sensor status) on a TFT screen.
# Components
ESP32: Microcontroller for managing all sensors and handling Blynk integration.

TFT Display (ST7789): A display to show real-time sensor data and system status.

LDR Sensor: Detects light intensity to adjust the street lights automatically.

PIR Sensors: Detects motion to activate the street lights.

Buzzer: Used for emergency alerts.

LEDs: Indicate the status of street lights.

Blynk Mobile App: Controls the system remotely, monitors sensor data, and triggers emergency alerts.

# Wiring
LDR: Connected to pin 34 of the ESP32.

PIR Sensors: Connected to pins 25, 26, and 27 of the ESP32.

LEDs: Connected to pins 12, 13, and 14 of the ESP32.

Buzzer: Connected to pin 32 of the ESP32.

Button: Connected to pin 33 for emergency alert toggling.

TFT Display: Connected to pins 5, 2, 4, 18, and 23 for communication.

# Blynk Integration
The project uses the Blynk platform to control and monitor the system in real-time. You will need to:

Create a Blynk account and set up a project in the Blynk app.
Use the authentication token provided by Blynk in your code.

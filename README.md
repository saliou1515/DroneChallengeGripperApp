# DroneChallengeGripperApp
Arduino C++ sketch for a NodeMCU D1 Mini (ESP8266) that hosts a web page to open and close a drone's claw gripper. Built for my high school's TSA State Drone Challenge drone (finalist, 2025).

## How it works
- The board connects to Wi-Fi and hosts a web server.
- The page shows the gripper status (OPEN or CLOSED) and a TOGGLE button.
- Pressing the button sends a PWM signal to the servo on pin D2 (1850 µs open, 2500 µs closed).

## Setup
1. Enter your Wi-Fi name and password in `gripper_control.ino`.
2. Upload it with the Arduino IDE (ESP8266 board package).
3. Open the Serial Monitor to get the board's IP address, then visit it in a browser.

## Hardware
NodeMCU D1 Mini, servo on D2, powered through separate 5V regulators to protect the flight controller.

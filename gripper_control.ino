#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

ESP8266WebServer server(80);
Servo myServo;

const int servoPin = D2;

bool isOpen = false;

const int GRIP_CLOSED = 2500;
const int GRIP_OPEN = 1850;

void handleRoot() {
  String state = isOpen ? "OPEN" : "CLOSED";
  String color = isOpen ? "green" : "red";

  String html = "<html><body style='text-align:center; font-family:sans-serif;'>";
  html += "<h1>Gripper Control</h1>";
  html += "<p style='font-size:24px;'>Status: <strong style='color:" + color + ";'>" + state + "</strong></p>";
  html += "<a href=\"/toggle\"><button style='font-size:30px; padding:20px 40px;'>TOGGLE</button></a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleToggle() {
  isOpen = !isOpen;
  myServo.writeMicroseconds(isOpen ? GRIP_OPEN : GRIP_CLOSED);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  myServo.attach(servoPin);
  myServo.writeMicroseconds(GRIP_CLOSED);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to WiFi!");
    return;
  }

  Serial.println("\nConnected!");
  Serial.print("Go to: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.begin();
}

void loop() {
  server.handleClient();
}

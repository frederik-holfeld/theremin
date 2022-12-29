#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

// Pin definitions
#define trig1 D0
#define echo1 D1

#define trig2 D7
#define echo2 D8

#define led   D4


// Credentials for network connection
char* ssid = "CHANGE_ME!";
char* pass = "CHANGE_ME_TOO!";

// Create UDP object and set IP-address and port of the SC server.
WiFiUDP udp;
IPAddress ip(42, 42, 42, 42);
short port = 1337; 

// Variables for sensors
int duration1;
int duration2;


void setup() {
  // Serial baud rate
  Serial.begin(115200);

  // Serial messages on startup
  Serial.printf("Theremin V1!\n");
  Serial.printf("Trying to connect to %s", ssid);

  // Set pin modes.
  pinMode(led, OUTPUT);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);

  // Use password if one is given, otherwise try to connect without password.
  // Wi-Fi connection did not work with password protected Wi-Fi for me yet, so fall back to unprotected guest Wi-Fi.
  if (strlen(pass) != 0) WiFi.begin(ssid, pass);  
  else WiFi.begin(ssid);

  // Make LED blink while connecting, so one can know what's going on when no serial connection is present.
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(led, LOW);
    delay(100);
    digitalWrite(led, HIGH);
    delay(100);
  }

  Serial.printf("Connected to %s.\n", ssid);
  Serial.printf("IP: %s.\n", WiFi.localIP());

  udp.begin(1337);
}

void loop() {
  // Read first sensor.
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);

  // Read second sensor.
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);

  // Pack the 2 values into an OSC message and send it via the UDP object.
  OSCMessage message("/theremin");
  message.add(duration1);
  message.add(duration2);
  udp.beginPacket(ip, port);
  message.send(udp);
  udp.endPacket();
  message.empty();
}

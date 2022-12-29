#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

//pindefinitions
#define trig1 D0
#define echo1 D1
#define trig2 D7
#define echo2 D8
#define led   D4

//credentials for network connection
char* ssid = "FRITZ!Box Gastzugang";
char* pass = "";

//create udp object and set ip address and port of the sc server
WiFiUDP udp;
IPAddress ip(192, 168, 179, 23);
short port = 1337; 

//variables for sensors
int duration1;
int duration2;
//int distance1;
//int distance2;

void setup() {
  Serial.begin(115200);

  Serial.println("theremin v1!");
  Serial.printf("trying to connect to %s", ssid);

  pinMode(led, OUTPUT);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);

  //use password if one is given, otherwise try to connect without password
  //wifi connection did not work with password protected wifi, fell back to unprotected guest wifi
  if (strlen(pass) != 0) WiFi.begin(ssid, pass);  
  else WiFi.begin(ssid);

  //make led blink while connecting, so one can know what's going on when no serial connection is present
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(led, LOW);
    delay(100);
    digitalWrite(led, HIGH);
    delay(100);
  }

  Serial.printf("connected to %s.\n", ssid);
  Serial.printf("ip: %s.\n", WiFi.localIP());

  udp.begin(1337);
}

void loop() {
  //read first sensor
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  //distance1 = duration1 * 0.017;

  //read second sensor
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  //distance2 = duration2 * 0.017;

  //some code is commented out for better performance in the loop
  //Serial.printf("distance1 is %dcm, distance2 is %dcm!\n", distance1, distance2);

  //pack the 2 values into an osc message and send it via the udp object
  OSCMessage message("/theremin");
  message.add(duration1);
  message.add(duration2);
  udp.beginPacket(ip, port);
  message.send(udp);
  udp.endPacket();
  message.empty();
}

#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>

// ==================================================Start Configuration==================================================

const char* ssid = "R's Network"; // no default
const char* passwd = "RobbyIsCool"; // default = NULL or ""
#define channel 3 // default = 1
#define hidden 0  // default = 0
//const int maxConnections = 4; // default = 4

#define useConfig true
const IPAddress accessPointIP = IPAddress(10, 2, 13, 1);
const IPAddress subnet = IPAddress(255, 255, 255, 0);

//const int serialSpeed = 115200;
#define serialSpeed 250000
#define serialTimeout 25

#define numUsers 2
// {"username", "password", "name", "chatHistory", "warnings"},
const String users[numUsers][5] = {
  {"R", "Robby", "Robby", "", "warnings"},
  {"A", "Aug", "Andrew", "", "warnings"}
};

// ===================================================End Configuration===================================================

IPAddress ip;
ESP8266WebServer server(80);

const String redirectURL = "/chat";

void addToChat (String n, String s, String m, bool allowAdmin = false);
void serverMessageSend(String m, String s = "Server Message");

void setup() {
  // put your setup code here, to run once:
  startSerial();
  startAP();
  startServer();
}

int Loop = 0;
String serialM[] = {"", ""};
String messages[] = {"Subject: ", "Message: "};

void loop(void) {
  // put your main code here, to run repeatedly:
  //  WiFiClient client = server.client();
  //  Serial.print("[AP] new clinet, IP=");
  //  Serial.println(client.remoteIP());

  server.handleClient();

  if (Serial.available() > 0) {
    if (Loop < 2) {
      serialM[Loop] = Serial.readString();
      Serial.print(messages[Loop]);
      Serial.println(serialM[Loop]);
      Loop++;
    } else {
      Loop = 0;
      Serial.println("Message posted");
      addToChat("Admin", serialM[0], serialM[1], true);
    }
  }

  if (Loop >= 2) {
    Loop = 0;
    Serial.println("Message posted");
    addToChat("Admin", serialM[0], serialM[1], true);
  }
}

void startSerial() {
  Serial.begin(serialSpeed);
  Serial.setTimeout(serialTimeout);
  Serial.println("\n");
}

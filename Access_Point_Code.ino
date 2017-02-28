bool startAP() {
  Serial.println("Preparing to start AP");
  delay(500);
  bool softApConfigBool;
  bool softApBool;
  Serial.print("Starting AP");
  if (useConfig) {
    softApConfigBool = WiFi.softAPConfig(accessPointIP, accessPointIP, subnet);
    if (softApConfigBool) {
      Serial.write('.');
    } else {
      Serial.println("\n");
      Serial.print("Error code 1: ");
      Serial.println("AP config error");
      Serial.println("\n");
      return false;
    }
  } else {
    Serial.write('.');
  }
  //  softApBool = WiFi.softAP(ssid, passwd, channel, hidden, maxConnections);
  softApBool = WiFi.softAP(ssid, passwd, channel, hidden);
  if (softApBool) {
    Serial.write('.');
  } else {
    Serial.println("\n");
    Serial.print("Error code 2: ");
    Serial.println("AP start error");
    Serial.println("\n");
    return false;
  }
  ip = WiFi.softAPIP();
  Serial.write('.');
  Serial.println(" done");
  Serial.println("IP address is: " + ip.toString());
}

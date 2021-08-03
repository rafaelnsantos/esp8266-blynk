#ifndef WiFiManager_h
#define WiFiManager_h

#include "Arduino.h"

#include "ESP8266WiFi.h"
#include "ESP8266mDNS.h"
#include "ArduinoOTA.h"

#include "API.h"
#include "Data.h"
#include "Debugger.h"

class WiFiManager
{
private:
  bool connected;
  void setupAP(String ssid, String password);
  bool testWifi(String ssid, String password);
  void setupOTAUpdate();
  void setupMDNS(String hostname);

  char blynkToken[33];
  int previousSwitchFlag = 0;

public:
  bool begin();
  void run();
};

extern WiFiManager wifi;

#endif
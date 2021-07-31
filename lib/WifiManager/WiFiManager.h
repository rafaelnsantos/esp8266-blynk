#ifndef WiFiManager_h
#define WiFiManager_h

#define ATOMIC_FS_UPDATE

#include "Arduino.h"

#include "ESP8266WiFi.h"
#include "ESP8266mDNS.h"
#include "ArduinoOTA.h"

#include "API.h"
#include "OTAEEPROM.h"
#include "Debugger.h"

class WiFiManager
{
private:
  API api;
  bool connected;
  void setupAP(String ssid, String password);
  bool testWifi();
  void setupOTAUpdate();
  void setupMDNS(String hostname);
  void setupBlynk();
  void setupSwitch();
  void runSwitch();

  char blynkToken[33];
  int previousSwitchFlag = 0;

public:
  void begin();
  void run();
  void reset();
  bool isConnected();
};

#endif
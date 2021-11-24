#ifndef WiFiManager_h
#define WiFiManager_h

#include "Arduino.h"

#include "ESP8266WiFi.h"

#include "API.h"
#include "Data.h"
#include "Debugger.h"
#include "WiFiUtil.h"

class WiFiManager
{
private:
  API api;
  bool connected = false;
  void setupAP();

public:
  bool begin();
  void run();
  bool isConnected();
};

extern WiFiManager wifi;

#endif
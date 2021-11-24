#ifndef WIFIUTIL_H
#define WIFIUTIL_H

#include "Arduino.h"

#include "ESP8266WiFi.h"
#include "ArduinoJson.h"
#include "Debugger.h"

typedef std::function<void(const DynamicJsonDocument &)> ScanCallback;

class WiFiUtil
{
public:
  static bool testWifi(String ssid, String password);
  static void scanNetworkAsync(ScanCallback callback);
  static DynamicJsonDocument scanNetwork();
};

#endif
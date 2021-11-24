#ifndef API_h
#define API_h

#include <Arduino.h>

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "Debugger.h"
#include "Data.h"
#include "PracticalCrypto.h"
#include "WiFiUtil.h"

class API
{
private:
  ESP8266WebServer server;
  void handleScan();
  void handleConfig();
  void handleReset();
  void handleStats();

public:
  void begin(bool connected);
  API(): server(80) {}
  void run();
};

#endif
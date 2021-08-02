#ifndef API_h
#define API_h

#include <Arduino.h>

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "user_interface.h"
#include "Debugger.h"
#include "OTAEEPROM.h"
#include <ESP8266httpUpdate.h>

#define ATOMIC_FS_UPDATE

class API
{
private:
  ESP8266WebServer server;
  void handleScan();
  void handleWifi();
  void handleConfig();
  void handleAuth();
  void handleReset();
  void handleUpdate();
  void handleName();

public:
  void begin(boolean connected);
  API(): server(80) {}
  void run();
};

extern API api;

#endif
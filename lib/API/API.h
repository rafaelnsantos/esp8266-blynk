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
  void handleScan();
  void handleWifi();
  void handleConfig();
  void handleAuth();
  void handleReset();
  void handleUpdate();

public:
  void begin(boolean connected);

  void run();
};

#endif
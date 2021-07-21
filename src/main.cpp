// #define DEBUG

#include "Arduino.h"

#include "Debugger.h"
#include "WiFiManager.h"

WiFiManager wifiManager;

void setup()
{
  Debugger::begin();

  wifiManager.begin();
}

void loop()
{
  wifiManager.run();
}
#include "Arduino.h"

#include "WiFiManager.h"

WiFiManager wifiManager;

void setup()
{
  wifiManager.begin();
}

void loop()
{
  wifiManager.run();
}
#include "Arduino.h"

#include "WiFiManager.h"
#include "BlynkManager.h"

void setup()
{
  wifi.begin();

  blynk.begin(wifi.isConnected());
}

void loop()
{
  blynk.run(wifi.isConnected());

  wifi.run();
}
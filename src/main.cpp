#include "Arduino.h"

#include "WiFiManager.h"
#include "BlynkManager.h"
#include "SinricManager.h"
#include "Relay.h"
#include "Switch.h"

void setup()
{
  wifi.begin();

  relay.begin();
  button.begin();
  
  if (wifi.isConnected())
  {
    sinric.begin();
    blynk.begin();
  }
}

void loop()
{
  wifi.run();

  button.run();

  if (wifi.isConnected())
  {
    blynk.run();
    sinric.run();
  }
}
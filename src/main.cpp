#include "Arduino.h"

#include "WiFiManager.h"
#include "BlynkManager.h"
#include "SinricManager.h"
#include "Relay.h"
#include "Switch.h"

bool connected;

void setup()
{
  connected = wifi.begin();
  relay.begin();
  button.begin();
  
  if (connected)
  {
    sinric.begin();
    blynk.begin();
  }
}

void loop()
{
  wifi.run();

  button.run();

  if (connected)
  {
    blynk.run();
    sinric.run();
  }
}
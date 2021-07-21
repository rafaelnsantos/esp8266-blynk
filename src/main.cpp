// #define DEBUG

#include "Arduino.h"

#include "Debugger.h"
#include "WiFiManager.h"

#define RESET_PIN 0

WiFiManager wifiManager;

void setup()
{
  Debugger::begin();

  wifiManager.begin();

#ifndef DEBUG
  pinMode(RESET_PIN, INPUT);
#endif
}

void loop()
{
  wifiManager.run();

#ifndef DEBUG
  if (digitalRead(RESET_PIN) == LOW)
  {
    wifiManager.reset();
  }
#endif
}
#ifndef BLYNKMANAGER_H
#define BLYNKMANAGER_H

#include "Arduino.h"

#include "Data.h"
#include "Debugger.h"
#include "Relay.h"

class BlynkManager
{
private:
  char blynkToken[33];

public:
  void begin();
  void run();
  void setState(int state);
};

extern BlynkManager blynk;

#endif
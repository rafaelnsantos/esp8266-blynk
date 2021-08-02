#ifndef BLYNKMANAGER_H
#define BLYNKMANAGER_H

#include "Arduino.h"

#include "OTAEEPROM.h"
#include "Debugger.h"

class BlynkManager
{
private:
  void setupBlynk();
  void setupSwitch();
  void runSwitch();

  char blynkToken[33];
  int previousSwitchFlag = 0;

public:
  void begin(bool hasInternet);
  void run(bool hasInternet);
  bool isConnected();
};

extern BlynkManager blynk;

#endif
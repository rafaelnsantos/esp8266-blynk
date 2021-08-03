#ifndef SINRICMANAGER_H
#define SINRICMANAGER_H

#include "Arduino.h"

#include "Data.h"
#include "Debugger.h"
#include "Relay.h"

class SinricManager
{

public:
  void begin();
  void run();
  void sendPowerState(bool state, String reason);
};

extern SinricManager sinric;

#endif
#ifndef RELAY_H
#define RELAY_H

#include "Arduino.h"
#include "Data.h"
#include "Debugger.h"

class Relay
{
private:
  int PIN;
  bool INVERTED = false;

public:
  Relay(int pin);
  Relay(int pin, bool isInverted);
  void begin();
  void setState(bool state);
  bool toggle();
  bool getState();
  void recoverState();
};

#endif
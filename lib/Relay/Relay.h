#ifndef RELAY_H
#define RELAY_H

#include "Arduino.h"

#include "SinricManager.h"

enum REASON {
  SWITCH,
  BLYNK,
  SINRIC
};

class Relay
{
private:
  int PIN;

public:
  void begin();
  void setState(int state, REASON reason);
  void toggle();

  Relay(int pin){
    PIN = pin;
  }
};

extern Relay relay;

#endif
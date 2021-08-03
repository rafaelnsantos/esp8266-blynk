#ifndef SWITCH_H
#define SWITCH_H

#include "Arduino.h"
#include "Relay.h"

class Switch
{
private:
  int PIN;
  int previousState;

public:
  void begin();
  void run();

  Switch(int pin){
    PIN = pin;
  }
};

extern Switch button;

#endif
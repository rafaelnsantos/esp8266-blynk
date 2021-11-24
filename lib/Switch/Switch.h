#ifndef SWITCH_H
#define SWITCH_H

#include "Arduino.h"

using SwitchCallback = std::function<void(const int &)>;

class Switch
{
private:
  int PIN;
  int previousState;
  SwitchCallback switchCallback;

public:
  void begin();
  void run();
  void onSwitch(SwitchCallback cb);

  Switch(int pin){
    PIN = pin;
  }
};

#endif
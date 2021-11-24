#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

using ButtonCallback = std::function<void()>;

class Button
{
private:
  int PIN;
  int previousState;
  ButtonCallback onPressCallback;
  ButtonCallback onReleaseCallback;

public:
  void begin();
  void run();
  void onPress(ButtonCallback cb);
  void onRelease(ButtonCallback cb);

  Button(int pin){
    PIN = pin;
  }
};

#endif
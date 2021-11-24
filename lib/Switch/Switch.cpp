#include "Switch.h"

void Switch::begin()
{
  pinMode(PIN, FUNCTION_3);
  pinMode(PIN, INPUT_PULLUP);

  previousState = digitalRead(PIN);
}

void Switch::run()
{
  int currentState = digitalRead(PIN);

  if (currentState != previousState)
  {
    if (switchCallback)
    {
      switchCallback(currentState);
    }

    previousState = currentState;
  }
}

void Switch::onSwitch(SwitchCallback cb)
{
  switchCallback = cb;
}

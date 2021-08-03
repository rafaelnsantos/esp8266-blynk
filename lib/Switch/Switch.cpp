#include "Switch.h"

Switch button(3);

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
    relay.toggle();
    previousState = currentState;
  }
}

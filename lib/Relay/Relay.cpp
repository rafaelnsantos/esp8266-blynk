#include "Relay.h"

Relay::Relay(int pin)
{
  PIN = pin;
}

Relay::Relay(int pin, bool isInverted)
{
  PIN = pin;
  INVERTED = isInverted;
}

void Relay::begin()
{
  pinMode(PIN, OUTPUT);

  recoverState();
}

void Relay::setState(bool state)
{
  data.saveRelay(state);

  if (INVERTED) state = !state;

  int newState = state ? HIGH : LOW;

  DEBUG_PRINT(state);

  digitalWrite(PIN, newState);
}

bool Relay::toggle()
{
  int state = getState();
  
  setState(!state);
  
  return !state;
}

bool Relay::getState()
{
  int state = digitalRead(PIN);

  if (INVERTED)
  {
    return state == LOW ? true : false;
  }

  return state == HIGH ? true : false;
}

void Relay::recoverState()
{
  bool state = data.getRelay();

  setState(state);
}

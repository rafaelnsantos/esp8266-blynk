#include "Relay.h"
#include "BlynkManager.h"

Relay relay(0);

void Relay::begin()
{
  pinMode(PIN, OUTPUT);
}

void Relay::setState(int state, REASON reason)
{
  int oldState = digitalRead(PIN);
  
  if (state == oldState) return;
  
  DEBUG_PRINT(state);
  digitalWrite(PIN, state);

  switch (reason)
  {
  case BLYNK:
    DEBUG_PRINT("BLYNK");
    sinric.sendPowerState(state == 0 ? true : false, "blynk");
    break;

  case SINRIC:
    DEBUG_PRINT("SINRIC");
    blynk.setState(state);
    break;
  
  case SWITCH:
    DEBUG_PRINT("SWITCH");
    sinric.sendPowerState(state == 0 ? true : false, "manual switch");
    blynk.setState(state);
    break;
  }
}

void Relay::toggle()
{
  setState(digitalRead(PIN) == LOW ? HIGH : LOW, SWITCH);
}

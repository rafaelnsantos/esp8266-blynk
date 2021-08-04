#include "BlynkManager.h"
#include <BlynkSimpleEsp8266.h>

BlynkManager blynk;

BLYNK_WRITE(V0)
{
  relay.setState(param.asInt(), BLYNK);
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);
}

void BlynkManager::begin()
{
  String token = data.getAuth();
  token.toCharArray(blynkToken, 33);
  Blynk.config(blynkToken);
}

void BlynkManager::run()
{
  Blynk.run();
}

void BlynkManager::setState(int state)
{
  if (Blynk.connected()) Blynk.virtualWrite(V0, state);
}
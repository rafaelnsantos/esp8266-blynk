#include "SinricManager.h"
#include <SinricPro.h>
#include <SinricProSwitch.h>

SinricManager sinric;

SinricProSwitch * mySwitch;

bool onPowerState(const String &deviceId, bool &state) {
  relay.setState(state ? LOW : HIGH, SINRIC);
  return true;
}

void SinricManager::begin()
{
  DEBUG_PRINT("setupSinric");

  String APP_KEY = data.getAppKey();
  String APP_SECRET = data.getAppSecret();
  String SWITCH_ID = data.getSwitchID();

  SinricProSwitch& aux = SinricPro[SWITCH_ID];
  mySwitch = &aux;
  mySwitch->onPowerState(onPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void SinricManager::run()
{
  SinricPro.handle();
}

void SinricManager::sendPowerState(bool state, String reason)
{
  if (SinricPro.isConnected()) mySwitch->sendPowerStateEvent(state, reason);
}

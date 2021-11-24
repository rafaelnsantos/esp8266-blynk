#include "Arduino.h"

#include "Debugger.h"
#include "WiFiManager.h"
#include "Relay.h"
#include "Switch.h"
#include "Button.h"
#include "Data.h"

#include <SinricPro.h>
#include <SinricProSwitch.h>

Button button(1);
Switch mySwitch(3);
Relay relay(0);
SinricProSwitch * device;

void switchCallback(int _)
{
  bool state = relay.toggle();
  if (SinricPro.isConnected())
  {
    device->sendPowerStateEvent(state, "manual switch");
  }
}

void buttonPressCallback()
{
  DEBUG_PRINT("reset button pressed");
  data.erase();

  ESP.restart();
}

bool onPowerState(const String &deviceId, bool &state) {
  relay.setState(state);
  return true;
}

void setupSinricPro()
{
  String APP_KEY = data.getAppKey();
  String APP_SECRET = data.getAppSecret();
  String SWITCH_ID = data.getSwitchID();
  device = &SinricPro[SWITCH_ID].as<SinricProSwitch>();

  device->onPowerState(onPowerState);

  SinricPro.restoreDeviceStates(true);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup()
{
  Debug.begin();

  data.begin();
  button.begin();
  relay.begin();
  mySwitch.begin();


  mySwitch.onSwitch(switchCallback);
  button.onPress(buttonPressCallback);

  wifi.begin();
  
  if (wifi.isConnected())
  {
    setupSinricPro();
  }
}

void loop()
{
  wifi.run();

  mySwitch.run();
  button.run();

  if (wifi.isConnected())
  {
    SinricPro.handle();
  }

  Debug.run();
}
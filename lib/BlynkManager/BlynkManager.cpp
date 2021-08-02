#include "BlynkManager.h"
#include <BlynkSimpleEsp8266.h>

#define SWITCH_PIN 3
#define RELAY_PIN 0

bool connected = false;

BlynkManager blynk;

BLYNK_WRITE(V0)
{
  digitalWrite(RELAY_PIN, param.asInt());
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);
  connected = true;
}

BLYNK_DISCONNECTED()
{
  connected = false;
}

void BlynkManager::begin(bool hasInternet)
{
  if (hasInternet) setupBlynk();

  setupSwitch();
}

void BlynkManager::run(bool hasInternet)
{
  runSwitch();

  if (hasInternet) Blynk.run();
}

bool BlynkManager::isConnected()
{
  return connected;
}


void BlynkManager::setupBlynk()
{
  String token = eeprom.getAuth();
  token.toCharArray(blynkToken, 33);
  Blynk.config(blynkToken);
}

void BlynkManager::setupSwitch()
{
  pinMode(SWITCH_PIN, FUNCTION_3);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  previousSwitchFlag = digitalRead(SWITCH_PIN);
}

void BlynkManager::runSwitch()
{
  int currentSwitch = digitalRead(SWITCH_PIN);

  if (currentSwitch != previousSwitchFlag) {
    int state = digitalRead(RELAY_PIN) == LOW ? HIGH : LOW;
    digitalWrite(RELAY_PIN, state);
    DEBUG_PRINT("SWITCH");
    DEBUG_PRINT(state);
    Blynk.virtualWrite(V0, state);
    previousSwitchFlag = currentSwitch;
  }
}